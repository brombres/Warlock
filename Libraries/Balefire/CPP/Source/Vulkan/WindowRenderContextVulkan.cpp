#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

const Byte fragment_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 19, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 7, 0, 4, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 9, 0, 0, 0, 12, 0, 0, 0, 16, 0, 3, 0,
  4, 0, 0, 0, 7, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 9, 0, 0, 0,
  111, 117, 116, 67, 111, 108, 111, 114, 0, 0, 0, 0, 5, 0, 5, 0,
  12, 0, 0, 0, 102, 114, 97, 103, 67, 111, 108, 111, 114, 0, 0, 0,
  71, 0, 4, 0, 9, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  71, 0, 4, 0, 12, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0, 3, 0, 0, 0,
  2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0, 32, 0, 0, 0,
  23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0,
  32, 0, 4, 0, 8, 0, 0, 0, 3, 0, 0, 0, 7, 0, 0, 0,
  59, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0, 3, 0, 0, 0,
  23, 0, 4, 0, 10, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 11, 0, 0, 0, 1, 0, 0, 0, 10, 0, 0, 0,
  59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0, 0, 0, 128, 63,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 61, 0, 4, 0,
  10, 0, 0, 0, 13, 0, 0, 0, 12, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 15, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
  81, 0, 5, 0, 6, 0, 0, 0, 16, 0, 0, 0, 13, 0, 0, 0,
  1, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0, 17, 0, 0, 0,
  13, 0, 0, 0, 2, 0, 0, 0, 80, 0, 7, 0, 7, 0, 0, 0,
  18, 0, 0, 0, 15, 0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0,
  14, 0, 0, 0, 62, 0, 3, 0, 9, 0, 0, 0, 18, 0, 0, 0,
  253, 0, 1, 0, 56, 0, 1, 0
};

const Byte vertex_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 54, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 10, 0, 0, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 12, 0, 0, 0, 23, 0, 0, 0, 34, 0, 0, 0,
  38, 0, 0, 0, 49, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 12, 0, 0, 0,
  112, 111, 115, 105, 116, 105, 111, 110, 115, 0, 0, 0, 5, 0, 4, 0,
  23, 0, 0, 0, 99, 111, 108, 111, 114, 115, 0, 0, 5, 0, 6, 0,
  32, 0, 0, 0, 103, 108, 95, 80, 101, 114, 86, 101, 114, 116, 101, 120,
  0, 0, 0, 0, 6, 0, 6, 0, 32, 0, 0, 0, 0, 0, 0, 0,
  103, 108, 95, 80, 111, 115, 105, 116, 105, 111, 110, 0, 6, 0, 7, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 103, 108, 95, 80, 111, 105, 110, 116,
  83, 105, 122, 101, 0, 0, 0, 0, 6, 0, 7, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 103, 108, 95, 67, 108, 105, 112, 68, 105, 115, 116, 97,
  110, 99, 101, 0, 6, 0, 7, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  103, 108, 95, 67, 117, 108, 108, 68, 105, 115, 116, 97, 110, 99, 101, 0,
  5, 0, 3, 0, 34, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0,
  38, 0, 0, 0, 103, 108, 95, 86, 101, 114, 116, 101, 120, 73, 110, 100,
  101, 120, 0, 0, 5, 0, 5, 0, 49, 0, 0, 0, 102, 114, 97, 103,
  67, 111, 108, 111, 114, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 72, 0, 5, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 11, 0, 0, 0, 1, 0, 0, 0,
  72, 0, 5, 0, 32, 0, 0, 0, 2, 0, 0, 0, 11, 0, 0, 0,
  3, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  11, 0, 0, 0, 4, 0, 0, 0, 71, 0, 3, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 71, 0, 4, 0, 38, 0, 0, 0, 11, 0, 0, 0,
  42, 0, 0, 0, 71, 0, 4, 0, 49, 0, 0, 0, 30, 0, 0, 0,
  0, 0, 0, 0, 19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0,
  3, 0, 0, 0, 2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0,
  32, 0, 0, 0, 23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0,
  2, 0, 0, 0, 21, 0, 4, 0, 8, 0, 0, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0,
  3, 0, 0, 0, 28, 0, 4, 0, 10, 0, 0, 0, 7, 0, 0, 0,
  9, 0, 0, 0, 32, 0, 4, 0, 11, 0, 0, 0, 6, 0, 0, 0,
  10, 0, 0, 0, 59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0,
  6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 13, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0,
  0, 0, 0, 191, 44, 0, 5, 0, 7, 0, 0, 0, 15, 0, 0, 0,
  13, 0, 0, 0, 14, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  16, 0, 0, 0, 0, 0, 0, 63, 44, 0, 5, 0, 7, 0, 0, 0,
  17, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 44, 0, 5, 0,
  7, 0, 0, 0, 18, 0, 0, 0, 14, 0, 0, 0, 16, 0, 0, 0,
  44, 0, 6, 0, 10, 0, 0, 0, 19, 0, 0, 0, 15, 0, 0, 0,
  17, 0, 0, 0, 18, 0, 0, 0, 23, 0, 4, 0, 20, 0, 0, 0,
  6, 0, 0, 0, 3, 0, 0, 0, 28, 0, 4, 0, 21, 0, 0, 0,
  20, 0, 0, 0, 9, 0, 0, 0, 32, 0, 4, 0, 22, 0, 0, 0,
  6, 0, 0, 0, 21, 0, 0, 0, 59, 0, 4, 0, 22, 0, 0, 0,
  23, 0, 0, 0, 6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  24, 0, 0, 0, 0, 0, 128, 63, 44, 0, 6, 0, 20, 0, 0, 0,
  25, 0, 0, 0, 24, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0,
  44, 0, 6, 0, 20, 0, 0, 0, 26, 0, 0, 0, 13, 0, 0, 0,
  24, 0, 0, 0, 13, 0, 0, 0, 44, 0, 6, 0, 20, 0, 0, 0,
  27, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0,
  44, 0, 6, 0, 21, 0, 0, 0, 28, 0, 0, 0, 25, 0, 0, 0,
  26, 0, 0, 0, 27, 0, 0, 0, 23, 0, 4, 0, 29, 0, 0, 0,
  6, 0, 0, 0, 4, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0,
  30, 0, 0, 0, 1, 0, 0, 0, 28, 0, 4, 0, 31, 0, 0, 0,
  6, 0, 0, 0, 30, 0, 0, 0, 30, 0, 6, 0, 32, 0, 0, 0,
  29, 0, 0, 0, 6, 0, 0, 0, 31, 0, 0, 0, 31, 0, 0, 0,
  32, 0, 4, 0, 33, 0, 0, 0, 3, 0, 0, 0, 32, 0, 0, 0,
  59, 0, 4, 0, 33, 0, 0, 0, 34, 0, 0, 0, 3, 0, 0, 0,
  21, 0, 4, 0, 35, 0, 0, 0, 32, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 35, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0,
  32, 0, 4, 0, 37, 0, 0, 0, 1, 0, 0, 0, 35, 0, 0, 0,
  59, 0, 4, 0, 37, 0, 0, 0, 38, 0, 0, 0, 1, 0, 0, 0,
  32, 0, 4, 0, 40, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
  32, 0, 4, 0, 46, 0, 0, 0, 3, 0, 0, 0, 29, 0, 0, 0,
  32, 0, 4, 0, 48, 0, 0, 0, 3, 0, 0, 0, 20, 0, 0, 0,
  59, 0, 4, 0, 48, 0, 0, 0, 49, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 51, 0, 0, 0, 6, 0, 0, 0, 20, 0, 0, 0,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 62, 0, 3, 0,
  12, 0, 0, 0, 19, 0, 0, 0, 62, 0, 3, 0, 23, 0, 0, 0,
  28, 0, 0, 0, 61, 0, 4, 0, 35, 0, 0, 0, 39, 0, 0, 0,
  38, 0, 0, 0, 65, 0, 5, 0, 40, 0, 0, 0, 41, 0, 0, 0,
  12, 0, 0, 0, 39, 0, 0, 0, 61, 0, 4, 0, 7, 0, 0, 0,
  42, 0, 0, 0, 41, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0,
  43, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 44, 0, 0, 0, 42, 0, 0, 0, 1, 0, 0, 0,
  80, 0, 7, 0, 29, 0, 0, 0, 45, 0, 0, 0, 43, 0, 0, 0,
  44, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0, 65, 0, 5, 0,
  46, 0, 0, 0, 47, 0, 0, 0, 34, 0, 0, 0, 36, 0, 0, 0,
  62, 0, 3, 0, 47, 0, 0, 0, 45, 0, 0, 0, 61, 0, 4, 0,
  35, 0, 0, 0, 50, 0, 0, 0, 38, 0, 0, 0, 65, 0, 5, 0,
  51, 0, 0, 0, 52, 0, 0, 0, 23, 0, 0, 0, 50, 0, 0, 0,
  61, 0, 4, 0, 20, 0, 0, 0, 53, 0, 0, 0, 52, 0, 0, 0,
  62, 0, 3, 0, 49, 0, 0, 0, 53, 0, 0, 0, 253, 0, 1, 0,
  56, 0, 1, 0
};

WindowRenderContextVulkan::~WindowRenderContextVulkan()
{
  if (initialized)
  {
    initialized = false;

    for (size_t i=0; i<MAX_FRAMES_IN_FLIGHT; ++i)
    {
      device_dispatch.destroySemaphore( finished_semaphores[i], nullptr );
      device_dispatch.destroySemaphore( available_semaphores[i], nullptr );
      device_dispatch.destroyFence( in_flight_fences[i], nullptr );
    }

		device_dispatch.destroyCommandPool( command_pool, nullptr );

    device_dispatch.destroyPipeline( graphics_pipeline, nullptr );
    device_dispatch.destroyPipelineLayout( pipeline_layout, nullptr );
    device_dispatch.destroyRenderPass( render_pass, nullptr );

		for (int i=0; i<framebuffers.size(); i++)
    {
			device_dispatch.destroyFramebuffer( framebuffers[i], nullptr );
		}

    swapchain.destroy_image_views( swapchain_image_views );

    vkb::destroy_swapchain( swapchain );
    vkb::destroy_device( device );
    vkb::destroy_surface( renderer->vulkan_instance, surface );
  }
}

void WindowRenderContextVulkan::configure()
{
  _configure_device();
  _configure_swapchain();
  _configure_queues();
  _configure_render_pass();
  _configure_graphics_pipeline();
  _configure_framebuffers();
  _configure_command_pool();
  _configure_command_buffers();
  _configure_sync_objects();

  /*
	swapchain_images       = swapchain.get_images().value();
	swapchain_image_views  = swapchain.get_image_views().value();
	swapchain_image_format = swapchain.image_format;
	const uint32_t swapchain_count = swapchain_images.size();
  //TODO
  */

  /*
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
  */

  /*
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
  */
	initialized = true;
}

void WindowRenderContextVulkan::_configure_device()
{
	//vulkan 1.3 features
	//VkPhysicalDeviceVulkan13Features features{};
	//features.dynamicRendering = true;
	//features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	//features12.bufferDeviceAddress = true;
	//features12.descriptorIndexing = true;

	vkb::PhysicalDeviceSelector selector{ renderer->vulkan_instance };
	vkb::PhysicalDevice physical_device = vkb_require(
    selector
		.set_minimum_version(1,2)
		//.set_required_features_13(features)
		.set_required_features_12( features12 )
		.set_surface( surface )
		.select()
  );

	vkb::DeviceBuilder deviceBuilder{ physical_device };
	device = vkb_require( deviceBuilder.build() );
  device_dispatch = device.make_table();
}

void WindowRenderContextVulkan::_configure_swapchain()
{
  // Create swapchain
	vkb::SwapchainBuilder swapchainBuilder{ device };

	auto swapchain_build_result = swapchainBuilder
    //.set_desired_format( VK_FORMAT_B8G8R8A8_UNORM )
		.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( window->width, window->height )
    .set_old_swapchain( swapchain )
		.build();
  vkb::destroy_swapchain( swapchain );
  swapchain = swapchain_build_result.value();
}

void WindowRenderContextVulkan::_configure_queues()
{
  // Graphics Queue
	graphics_queue = vkb_require( device.get_queue(vkb::QueueType::graphics) );
	present_queue  = vkb_require( device.get_queue(vkb::QueueType::present) );
}

void WindowRenderContextVulkan::_configure_render_pass()
{
  // RenderPass
	VkAttachmentDescription color_attachment = {};
	color_attachment.format  = swapchain.image_format;
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

  VkSubpassDependency dependency = {};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo render_pass_info = {};
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render_pass_info.attachmentCount = 1;
	render_pass_info.pAttachments = &color_attachment;
	render_pass_info.subpassCount = 1;
	render_pass_info.pSubpasses = &subpass;
	render_pass_info.pDependencies = &dependency;

	VK_CHECK( "creating render pass",
    device_dispatch.createRenderPass(
      &render_pass_info,
      nullptr,
      &render_pass
    )
  );
}

void WindowRenderContextVulkan::_configure_graphics_pipeline()
{
  VkShaderModule vertex_module =
      _create_shader_module( vertex_spv, sizeof(vertex_spv) );
  VkShaderModule fragment_module =
      _create_shader_module( fragment_spv, sizeof(fragment_spv) );

  if (vertex_module == VK_NULL_HANDLE || fragment_module == VK_NULL_HANDLE)
  {
    fprintf( stderr, "[ERROR] Balefire Vulkan: failed to create shader module.\n" );
    abort();
  }

  VkPipelineShaderStageCreateInfo vertex_stage_info = {};
  vertex_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertex_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertex_stage_info.module = vertex_module;
  vertex_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo fragment_stage_info = {};
  fragment_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragment_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragment_stage_info.module = fragment_module;
  fragment_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo shader_stages[] =
      { vertex_stage_info, fragment_stage_info };

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = 0;
  vertex_input_info.vertexAttributeDescriptionCount = 0;

  VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = swapchain.extent.width;
  viewport.height = swapchain.extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = swapchain.extent;

  VkPipelineViewportStateCreateInfo viewport_state = {};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState color_blend_attachment = {};
  color_blend_attachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blending = {};
  color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &color_blend_attachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  VkPipelineLayoutCreateInfo pipeline_layout_info = {};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 0;
  pipeline_layout_info.pushConstantRangeCount = 0;

  if (VK_SUCCESS != device_dispatch.createPipelineLayout(
      &pipeline_layout_info, nullptr, &pipeline_layout))
  {
    fprintf( stderr, "[ERROR] Balefire Vulkan: failed to create pipeline layout.\n" );
    abort();
  }

  std::vector<VkDynamicState> dynamic_states =
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
    VK_DYNAMIC_STATE_DEPTH_BIAS
  };

  VkPipelineDynamicStateCreateInfo dynamic_info = {};
  dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
  dynamic_info.pDynamicStates = dynamic_states.data();

  VkGraphicsPipelineCreateInfo pipeline_info = {};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = shader_stages;
  pipeline_info.pVertexInputState = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState = &multisampling;
  pipeline_info.pColorBlendState = &color_blending;
  pipeline_info.pDynamicState = &dynamic_info;
  pipeline_info.layout = pipeline_layout;
  pipeline_info.renderPass = render_pass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

  VK_CHECK( "creating graphics pipeline",
    device_dispatch.createGraphicsPipelines(
      VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &graphics_pipeline
    )
  );

  device_dispatch.destroyShaderModule( fragment_module, nullptr );
  device_dispatch.destroyShaderModule( vertex_module, nullptr );
}

void WindowRenderContextVulkan::_configure_framebuffers()
{
  swapchain_images = swapchain.get_images().value();
  swapchain_image_views = swapchain.get_image_views().value();

  framebuffers.resize( swapchain_image_views.size() );

  for (size_t i=0; i<swapchain_image_views.size(); ++i)
  {
    VkImageView attachments[] = { swapchain_image_views[i] };

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass = render_pass;
    framebuffer_info.attachmentCount = 1;
    framebuffer_info.pAttachments = attachments;
    framebuffer_info.width = swapchain.extent.width;
    framebuffer_info.height = swapchain.extent.height;
    framebuffer_info.layers = 1;

    VK_CHECK(
      "creating framebuffer",
      device_dispatch.createFramebuffer(
        &framebuffer_info, nullptr, &framebuffers[i] )
    );
  }
}

void WindowRenderContextVulkan::_configure_command_pool()
{
  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.queueFamilyIndex =
      device.get_queue_index(vkb::QueueType::graphics).value();

  VK_CHECK(
    "creating command pool",
    device_dispatch.createCommandPool( &pool_info, nullptr, &command_pool )
  );
}

void WindowRenderContextVulkan::_configure_command_buffers()
{
  command_buffers.resize( framebuffers.size() );

  VkCommandBufferAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t)command_buffers.size();

  VK_CHECK(
    "creating command buffers",
    device_dispatch.allocateCommandBuffers( &allocInfo, command_buffers.data() )
  );

  for (size_t i=0; i<command_buffers.size(); ++i)
  {
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VK_CHECK(
      "beginning command buffer",
      device_dispatch.beginCommandBuffer( command_buffers[i], &begin_info )
    );

    VkRenderPassBeginInfo render_pass_info = {};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = render_pass;
    render_pass_info.framebuffer = framebuffers[i];
    render_pass_info.renderArea.offset = { 0, 0 };
    render_pass_info.renderArea.extent = swapchain.extent;
    VkClearValue clearColor{ { { 0.0f, 0.0f, 0.0f, 1.0f } } };
    render_pass_info.clearValueCount = 1;
    render_pass_info.pClearValues = &clearColor;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapchain.extent.width;
    viewport.height = (float)swapchain.extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchain.extent;

    device_dispatch.cmdSetViewport(command_buffers[i], 0, 1, &viewport);
    device_dispatch.cmdSetScissor(command_buffers[i], 0, 1, &scissor);

    device_dispatch.cmdBeginRenderPass(
      command_buffers[i],
      &render_pass_info,
      VK_SUBPASS_CONTENTS_INLINE
    );

    device_dispatch.cmdBindPipeline(
      command_buffers[i],
      VK_PIPELINE_BIND_POINT_GRAPHICS,
      graphics_pipeline
    );

    device_dispatch.cmdDraw( command_buffers[i], 3, 1, 0, 0 );
    device_dispatch.cmdEndRenderPass(command_buffers[i]);

    VK_CHECK(
      "ending command buffer",
      device_dispatch.endCommandBuffer( command_buffers[i] )
    );
  }
}

void WindowRenderContextVulkan::_configure_sync_objects()
{
  available_semaphores.resize( MAX_FRAMES_IN_FLIGHT );
  finished_semaphores.resize( MAX_FRAMES_IN_FLIGHT );
  in_flight_fences.resize( MAX_FRAMES_IN_FLIGHT );
  image_in_flight.resize( swapchain.image_count, VK_NULL_HANDLE );

  VkSemaphoreCreateInfo semaphore_info = {};
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fence_info = {};
  fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i=0; i<MAX_FRAMES_IN_FLIGHT; ++i)
  {
    VK_CHECK(
      "creating available semaphore",
      device_dispatch.createSemaphore(
        &semaphore_info,
        nullptr,
        &available_semaphores[i]
      )
    );
    VK_CHECK(
      "creating finished semaphore",
      device_dispatch.createSemaphore(
        &semaphore_info,
        nullptr,
        &finished_semaphores[i]
      )
    );
    VK_CHECK(
      "creating fence",
      device_dispatch.createFence( &fence_info, nullptr, &in_flight_fences[i] )
    );
  }
}

void WindowRenderContextVulkan::_recreate_swapchain()
{
  device_dispatch.deviceWaitIdle();
  device_dispatch.destroyCommandPool( command_pool, nullptr );

  for (auto framebuffer : framebuffers)
  {
    device_dispatch.destroyFramebuffer( framebuffer, nullptr );
  }

  swapchain.destroy_image_views( swapchain_image_views );

  _configure_swapchain();
  _configure_framebuffers();
  _configure_command_pool();
  _configure_command_buffers();
}

VkShaderModule WindowRenderContextVulkan::_create_shader_module( const Byte* code, int count )
{
  VkShaderModuleCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = count;
  create_info.pCode = (const uint32_t*)code;

  VkShaderModule shader_module;
  if (VK_SUCCESS !=
      device_dispatch.createShaderModule(&create_info, nullptr, &shader_module))
  {
    return VK_NULL_HANDLE; // failed to create shader module
  }

  return shader_module;
}

void WindowRenderContextVulkan::render()
{
printf("1 wait for fences\n");
  device_dispatch.waitForFences(
    1,
    &in_flight_fences[current_frame],
    VK_TRUE,
    UINT64_MAX
  );
printf("2 after fences\n");

  uint32_t image_index = 0;
  VkResult result = device_dispatch.acquireNextImageKHR(
    swapchain,
    UINT64_MAX,
    available_semaphores[current_frame],
    VK_NULL_HANDLE,
    &image_index
  );

  switch (result)
  {
    case VK_ERROR_OUT_OF_DATE_KHR:
      _recreate_swapchain();
      return;
    case VK_SUCCESS:
    case VK_SUBOPTIMAL_KHR:
      break;
    default:
      fprintf(
        stderr,
        "[ERROR] Balefire Vulkan: % (%s).\n",
        "error acquiring swapchain image",
        RendererVulkan::vkResult_to_c_string(result)
      );
      return;
  }

  if (image_in_flight[image_index] != VK_NULL_HANDLE)
  {
    device_dispatch.waitForFences(
      1,
      &image_in_flight[image_index],
      VK_TRUE,
      UINT64_MAX
    );
  }
  image_in_flight[image_index] = in_flight_fences[current_frame];

  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore wait_semaphores[] = { available_semaphores[current_frame] };
  VkPipelineStageFlags wait_stages[] =
    { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = wait_semaphores;
  submitInfo.pWaitDstStageMask = wait_stages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffers[image_index];

  VkSemaphore signal_semaphores[] = { finished_semaphores[current_frame] };
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signal_semaphores;

  device_dispatch.resetFences(1, &in_flight_fences[current_frame]);

  VK_CHECK(
    "submitting draw command buffer",
    device_dispatch.queueSubmit(
      graphics_queue,
      1, &submitInfo,
      in_flight_fences[current_frame]
    )
  );

  VkPresentInfoKHR present_info = {};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = signal_semaphores;

  VkSwapchainKHR swapChains[] = { swapchain };
  present_info.swapchainCount = 1;
  present_info.pSwapchains = swapChains;

  present_info.pImageIndices = &image_index;

  result = device_dispatch.queuePresentKHR(present_queue, &present_info);
  switch (result)
  {
    case VK_ERROR_OUT_OF_DATE_KHR:
    case VK_SUBOPTIMAL_KHR:
      _recreate_swapchain();
      return;
    case VK_SUCCESS:
      break;
    default:
      fprintf(
        stderr,
        "[ERROR] Balefire Vulkan: % (%s).\n",
        "error presenting swapchain image",
        RendererVulkan::vkResult_to_c_string(result)
      );
      return;
  }

  current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;

printf("8 wait idle\n");
  device_dispatch.deviceWaitIdle();
printf("8 after idle\n");

  /*
  uint32_t swapchain_index;
	VK_CHECK(
    vkAcquireNextImageKHR(
      device, swapchain, 2000000000, present_semaphore, nullptr, &swapchain_index
    )
  );

  VK_CHECK( vkWaitForFences( device, 1, &render_fences[swapchain_index], false, 2000000000 ) );
  VK_CHECK( vkResetFences( device, 1, &render_fences[swapchain_index] ) );

  if (frame_count % 100000 == 0) printf( "Render %d [%d]\n",frame_count,swapchain_index);

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

  ++frame_count;
  */
}
