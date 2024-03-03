#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;

#include "VkBootstrap.h"

void RendererVulkan::configure()
{
	vkb::InstanceBuilder builder( vkGetInstanceProcAddr );

	//make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name( "Warlock" )
		.request_validation_layers( true )
		.use_default_debug_messenger()
		.require_api_version(1, 2, 0)
		.build();

	vkb::Instance vkb_inst = inst_ret.value();

	vulkan_instance = vkb_inst.instance;
	vulkan_debug_messenger = vkb_inst.debug_messenger;
}

void RendererVulkan::configure_window( Window* window )
{
  /*
  WindowSDLVulkan* window_sdl_vulkan = (WindowSDLVulkan*)window;

	//vulkan 1.3 features
	//VkPhysicalDeviceVulkan13Features features{};
	//features.dynamicRendering = true;
	//features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 3)
		//.set_required_features_13(features)
		.set_required_features_12(features12)
		.set_surface(surface)
		.select()
		.value();

	//create the final vulkan device
	vkb::DeviceBuilder deviceBuilder{ physicalDevice };

	vkb::Device vkbDevice = deviceBuilder.build().value();

	// Get the VkDevice handle used in the rest of a vulkan application
	_device = vkbDevice.device;
	_chosenGPU = physicalDevice.physical_device;
  */
}
