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
	renderer_context->initialized = true;
}
