#include "Balefire/Vulkan/WindowRendererContextVulkan.h"
using namespace BALEFIRE;

WindowRendererContextVulkan::~WindowRendererContextVulkan()
{
  if (initialized)
  {
    initialized = false;

    delete[] command_buffers;
    delete[] render_fences;

		vkDestroyCommandPool( device, command_pool, nullptr );

		vkDestroySwapchainKHR( device, swapchain, nullptr );
		vkDestroyRenderPass(device, render_pass, nullptr);

		for (int i=0; i<framebuffers.size(); i++)
    {
			vkDestroyFramebuffer( device, framebuffers[i], nullptr );
			vkDestroyImageView( device, swapchain_image_views[i], nullptr );
		}

		vkDestroyDevice( device, nullptr );
		vkDestroySurfaceKHR( renderer->vulkan_instance, surface, nullptr );
  }
}

void WindowRendererContextVulkan::configure()
{
	//vulkan 1.3 features
	//VkPhysicalDeviceVulkan13Features features{};
	//features.dynamicRendering = true;
	//features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	//features12.bufferDeviceAddress = true;
	//features12.descriptorIndexing = true;

	vkb::PhysicalDeviceSelector selector{ renderer->vkb_instance };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1,2)
		//.set_required_features_13(features)
		.set_required_features_12( features12 )
		.set_surface( surface )
		.select()
		.value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };

	vkb::Device vkbDevice = deviceBuilder.build().value();

	device = vkbDevice.device;
	gpu    = physicalDevice.physical_device;

  // Create swapchain
	vkb::SwapchainBuilder swapchainBuilder
      { gpu, device, surface };

	vkb::Swapchain vkbSwapchain = swapchainBuilder
    //.set_desired_format( VK_FORMAT_B8G8R8A8_UNORM )
		.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( window->width, window->height )
		.build()
		.value();

	swapchain              = vkbSwapchain.swapchain;
	swapchain_images       = vkbSwapchain.get_images().value();
	swapchain_image_views  = vkbSwapchain.get_image_views().value();
	swapchain_image_format = vkbSwapchain.image_format;
	const uint32_t swapchain_count = swapchain_images.size();

  // Graphics Queue
	graphics_queue = vkbDevice.get_queue( vkb::QueueType::graphics ).value();
	graphics_queue_family = vkbDevice.get_queue_index( vkb::QueueType::graphics ).value();
	present_queue = vkbDevice.get_queue( vkb::QueueType::present ).value();

  // Command Pool
	VkCommandPoolCreateInfo cmd_pool_info = {};
	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.pNext = nullptr;

	cmd_pool_info.queueFamilyIndex = graphics_queue_family;
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VK_CHECK(
    vkCreateCommandPool(
      device,
      &cmd_pool_info,
      nullptr,
      &command_pool
    )
  );

  // Command Buffer
  VkCommandBufferAllocateInfo cmd_alloc_info = {};
  cmd_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmd_alloc_info.pNext = nullptr;

  cmd_alloc_info.commandPool = command_pool;
  cmd_alloc_info.commandBufferCount = swapchain_count;
  cmd_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  command_buffers = new VkCommandBuffer[ swapchain_count ];
  VK_CHECK(
    vkAllocateCommandBuffers(
      device, &cmd_alloc_info, command_buffers
    )
  );

  // RenderPass
	VkAttachmentDescription color_attachment = {};
	color_attachment.format  = swapchain_image_format;
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
      device,
      &render_pass_info,
      nullptr,
      &render_pass
    )
  );

  //-----------------------------
  /*
  vector<VkAttachmentDescription> attachments(1);

  //attachments[0].format = surfaceFormat.format;
  attachments[0].format = swapchain_image_format;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  //attachments[1].format = depthFormat;
  //attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
  //attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  //attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  //attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  //attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  //attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  //attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference colorReference = {};
  colorReference.attachment = 0;
  colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depthReference = {};
  depthReference.attachment = 1;
  depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpassDescription = {};
  subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpassDescription.colorAttachmentCount = 1;
  subpassDescription.pColorAttachments = &colorReference;
  //subpassDescription.pDepthStencilAttachment = &depthReference;
  subpassDescription.inputAttachmentCount = 0;
  subpassDescription.pInputAttachments = nullptr;
  subpassDescription.preserveAttachmentCount = 0;
  subpassDescription.pPreserveAttachments = nullptr;
  subpassDescription.pResolveAttachments = nullptr;

  vector<VkSubpassDependency> dependencies(1);

  dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
  dependencies[0].dstSubpass = 0;
  dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
  dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
  dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

  VkRenderPassCreateInfo renderPassInfo = {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  renderPassInfo.pAttachments = attachments.data();
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpassDescription;
  renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
  renderPassInfo.pDependencies = dependencies.data();

  vkCreateRenderPass(device, &renderPassInfo, nullptr, &render_pass);
  */
  //-----------------------------

  // Framebuffers
	VkFramebufferCreateInfo fb_info = {};
	fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	fb_info.pNext = nullptr;

	fb_info.renderPass = render_pass;
	fb_info.attachmentCount = 1;
	fb_info.width = window->width;
	fb_info.height = window->height;
	fb_info.layers = 1;

	framebuffers = std::vector<VkFramebuffer>( swapchain_count );
  render_fences = new VkFence[ swapchain_count ];

	for (int i=0; i<swapchain_count; i++)
  {
		fb_info.pAttachments = &swapchain_image_views[i];
		VK_CHECK(
      vkCreateFramebuffer(
        device,
        &fb_info,
        nullptr,
        &framebuffers[i]
      )
    );

    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.pNext = nullptr;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VK_CHECK(
      vkCreateFence(
        device,
        &fenceCreateInfo,
        nullptr,
        &render_fences[i]
      )
    );
	}

  // Synchronization

	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = nullptr;
	semaphoreCreateInfo.flags = 0;

	VK_CHECK(
    vkCreateSemaphore( device, &semaphoreCreateInfo, nullptr, &present_semaphore )
  );
	VK_CHECK(
    vkCreateSemaphore( device, &semaphoreCreateInfo, nullptr, &render_semaphore )
  );

	initialized = true;
}

void WindowRendererContextVulkan::render()
{
  uint32_t swapchain_index;
	VK_CHECK(
    vkAcquireNextImageKHR(
      device, swapchain, 2000000000, present_semaphore, nullptr, &swapchain_index
    )
  );

  VK_CHECK( vkWaitForFences( device, 1, &render_fences[swapchain_index], false, 2000000000 ) );
  VK_CHECK( vkResetFences( device, 1, &render_fences[swapchain_index] ) );

  if (frame_count % 100000 == 0) printf( "Render %d [%d]\n",frame_count,swapchain_index);

  /*
  VkCommandBuffer cmd_buffer = command_buffers[swapchain_index];
  VK_CHECK( vkResetCommandBuffer(cmd_buffer, 0) );
  VkCommandBufferBeginInfo cmd_begin_info = {};
	cmd_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//cmd_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	cmd_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	cmd_begin_info.pNext = nullptr;
	cmd_begin_info.pInheritanceInfo = nullptr;
	VK_CHECK( vkBeginCommandBuffer(cmd_buffer, &cmd_begin_info) );

  //make a clear-color from frame number. This will flash with a 120*pi frame period.
	VkClearValue clear_value;
	float flash = abs(sin(frame_count / 120.f));
	clear_value.color = { { 0.0f, 0.0f, flash, 1.0f } };

	//start the main renderpass.
	VkRenderPassBeginInfo rp_info = {};
	rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	rp_info.pNext = nullptr;

	rp_info.renderPass = render_pass;
	rp_info.renderArea.offset.x = 0;
	rp_info.renderArea.offset.y = 0;
	rp_info.renderArea.extent.width = window->width;
	rp_info.renderArea.extent.height = window->height;
	rp_info.framebuffer = framebuffers[swapchain_index];

	//connect clear values
	rp_info.clearValueCount = 1;
	rp_info.pClearValues = &clear_value;

	vkCmdBeginRenderPass( cmd_buffer, &rp_info, VK_SUBPASS_CONTENTS_INLINE );

  vkCmdEndRenderPass( cmd_buffer );
	VK_CHECK( vkEndCommandBuffer( cmd_buffer) );

  VkSubmitInfo submit_info = {};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.pNext = nullptr;
	//VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	submit_info.pWaitDstStageMask = &waitStage;
	submit_info.waitSemaphoreCount = 1;
	submit_info.pWaitSemaphores = &present_semaphore;
	submit_info.signalSemaphoreCount = 1;
	submit_info.pSignalSemaphores = &render_semaphore;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &cmd_buffer;
	VK_CHECK( vkQueueSubmit(graphics_queue, 1, &submit_info, render_fences[swapchain_index]) );

	VkPresentInfoKHR present_info = {};
	present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present_info.pNext = nullptr;
	present_info.pSwapchains = &swapchain;
	present_info.swapchainCount = 1;
	present_info.pWaitSemaphores = &render_semaphore;
	present_info.waitSemaphoreCount = 1;
	present_info.pImageIndices = &swapchain_index;
	VK_CHECK( vkQueuePresentKHR(present_queue, &present_info) );
  vkQueueWaitIdle( present_queue );
  */

  ++frame_count;
}
