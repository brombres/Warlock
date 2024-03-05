#include "Balefire/Core/Window.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRendererContextVulkan.h"
using namespace BALEFIRE;

RendererVulkan::~RendererVulkan()
{
  if (configured)
  {
    configured = false;
    vkb::destroy_debug_utils_messenger( vulkan_instance, debug_messenger );
    vkDestroyInstance( vulkan_instance, nullptr );
  }
}

void RendererVulkan::configure()
{
	vkb::InstanceBuilder builder( vkGetInstanceProcAddr );

	//make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name( "Warlock" )
		.request_validation_layers( true )
		.use_default_debug_messenger()
		.require_api_version(1, 2, 0)
		.build();

	vkb_instance = inst_ret.value();

	vulkan_instance = vkb_instance.instance;
	debug_messenger = vkb_instance.debug_messenger;
  configured = true;
}

void RendererVulkan::configure_window( Window* window )
{
  WindowRendererContextVulkan* renderer_context =
      (WindowRendererContextVulkan*) window->renderer_context.data;

	//vulkan 1.3 features
	//VkPhysicalDeviceVulkan13Features features{};
	//features.dynamicRendering = true;
	//features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

	vkb::PhysicalDeviceSelector selector{ vkb_instance };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1,2)
		//.set_required_features_13(features)
		.set_required_features_12( features12 )
		.set_surface( renderer_context->surface )
		.select()
		.value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };

	vkb::Device vkbDevice = deviceBuilder.build().value();

	renderer_context->device = vkbDevice.device;
	renderer_context->gpu    = physicalDevice.physical_device;

  // Create swapchain
	vkb::SwapchainBuilder swapchainBuilder
      { renderer_context->gpu, renderer_context->device, renderer_context->surface };

	vkb::Swapchain vkbSwapchain = swapchainBuilder
		.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( window->width, window->height )
		.build()
		.value();

	renderer_context->swapchain              = vkbSwapchain.swapchain;
	renderer_context->swapchain_images       = vkbSwapchain.get_images().value();
	renderer_context->swapchain_image_views  = vkbSwapchain.get_image_views().value();
	renderer_context->swapchain_image_format = vkbSwapchain.image_format;

  // Graphics Queue
	renderer_context->graphics_queue = vkbDevice.get_queue( vkb::QueueType::graphics ).value();
	renderer_context->graphics_queue_family = vkbDevice.get_queue_index( vkb::QueueType::graphics ).value();

  // Command Pool
	VkCommandPoolCreateInfo commandPoolInfo = {};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.pNext = nullptr;

	commandPoolInfo.queueFamilyIndex = renderer_context->graphics_queue_family;
	commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	VK_CHECK(
    vkCreateCommandPool(
      renderer_context->device,
      &commandPoolInfo,
      nullptr,
      &renderer_context->command_pool
    )
  );

  // Command Buffer
	VkCommandBufferAllocateInfo cmd_alloc_info = {};
	cmd_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmd_alloc_info.pNext = nullptr;

	cmd_alloc_info.commandPool = renderer_context->command_pool;
	cmd_alloc_info.commandBufferCount = 1;
	cmd_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	VK_CHECK(
    vkAllocateCommandBuffers(
      renderer_context->device, &cmd_alloc_info, &renderer_context->main_command_buffer
    )
  );

  // RenderPass
	VkAttachmentDescription color_attachment = {};
	color_attachment.format  = renderer_context->swapchain_image_format;
	color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	color_attachment.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	color_attachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  // Subpass
	VkAttachmentReference color_attachment_ref = {};
	color_attachment_ref.attachment = 0;
	color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachment_ref;

  // Main attachment
	VkRenderPassCreateInfo render_pass_info = {};
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	render_pass_info.attachmentCount = 1;
	render_pass_info.pAttachments = &color_attachment;
	render_pass_info.subpassCount = 1;
	render_pass_info.pSubpasses = &subpass;

	VK_CHECK(
    vkCreateRenderPass(
      renderer_context->device,
      &render_pass_info,
      nullptr,
      &renderer_context->render_pass
    )
  );

  // Framebuffers
	VkFramebufferCreateInfo fb_info = {};
	fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	fb_info.pNext = nullptr;

	fb_info.renderPass = renderer_context->render_pass;
	fb_info.attachmentCount = 1;
	fb_info.width = window->width;
	fb_info.height = window->height;
	fb_info.layers = 1;

	const uint32_t swapchain_image_count = renderer_context->swapchain_images.size();
	renderer_context->framebuffers = std::vector<VkFramebuffer>( swapchain_image_count );

	for (int i=0; i<swapchain_image_count; i++)
  {
		fb_info.pAttachments = &renderer_context->swapchain_image_views[i];
		VK_CHECK(
      vkCreateFramebuffer(
        renderer_context->device,
        &fb_info,
        nullptr,
        &renderer_context->framebuffers[i]
      )
    );
	}

	renderer_context->initialized = true;
}
