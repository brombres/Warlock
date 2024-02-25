#include "VulkanRenderer.h"
using namespace Warlock;

#include "VkBootstrap.h"

VulkanRenderer::VulkanRenderer()
{
}

VulkanRenderer::~VulkanRenderer()
{
}

void VulkanRenderer::configure()
{
	vkb::InstanceBuilder builder( vkGetInstanceProcAddr );

	//make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name( "Warlock" )
		.request_validation_layers( true )
		.use_default_debug_messenger()
		.require_api_version(1, 2, 0)
		.build();

	vkb::Instance vkb_inst = inst_ret.value();

	instance = vkb_inst.instance;
	debug_messenger = vkb_inst.debug_messenger;
}

  /*
  SDL_Vulkan_CreateSurface(_window, instance, &surface);

	//vulkan 1.3 features
	VkPhysicalDeviceVulkan13Features features{};
	features.dynamicRendering = true;
	features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

	//use vkbootstrap to select a gpu.
	//We want a gpu that can write to the SDL surface and supports vulkan 1.3 with the correct features
	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 3)
		.set_required_features_13(features)
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

// https://www.reddit.com/r/vulkan/comments/zxgst4/comment/j29a1kl/?utm_source=share&utm_medium=web2x&context=3
static const char* vkResult_to_c_string( VkResult result )
{
	switch (result)
  {
#define VK_RESULT_CASE(x) case VK_##x: return #x;
	VK_RESULT_CASE(SUCCESS)                        VK_RESULT_CASE(NOT_READY)
	VK_RESULT_CASE(TIMEOUT)                        VK_RESULT_CASE(EVENT_SET)
	VK_RESULT_CASE(EVENT_RESET)                    VK_RESULT_CASE(INCOMPLETE)
	VK_RESULT_CASE(ERROR_OUT_OF_HOST_MEMORY)       VK_RESULT_CASE(ERROR_OUT_OF_DEVICE_MEMORY)
	VK_RESULT_CASE(ERROR_INITIALIZATION_FAILED)    VK_RESULT_CASE(ERROR_DEVICE_LOST)
	VK_RESULT_CASE(ERROR_MEMORY_MAP_FAILED)        VK_RESULT_CASE(ERROR_LAYER_NOT_PRESENT)
	VK_RESULT_CASE(ERROR_EXTENSION_NOT_PRESENT)    VK_RESULT_CASE(ERROR_FEATURE_NOT_PRESENT)
	VK_RESULT_CASE(ERROR_INCOMPATIBLE_DRIVER)      VK_RESULT_CASE(ERROR_TOO_MANY_OBJECTS)
	VK_RESULT_CASE(ERROR_FORMAT_NOT_SUPPORTED)     VK_RESULT_CASE(ERROR_FRAGMENTED_POOL)
	VK_RESULT_CASE(ERROR_UNKNOWN)                  VK_RESULT_CASE(ERROR_OUT_OF_POOL_MEMORY)
	VK_RESULT_CASE(ERROR_INVALID_EXTERNAL_HANDLE)  VK_RESULT_CASE(ERROR_FRAGMENTATION)
	VK_RESULT_CASE(ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS)
	VK_RESULT_CASE(PIPELINE_COMPILE_REQUIRED)      VK_RESULT_CASE(ERROR_SURFACE_LOST_KHR)
	VK_RESULT_CASE(ERROR_NATIVE_WINDOW_IN_USE_KHR) VK_RESULT_CASE(SUBOPTIMAL_KHR)
	VK_RESULT_CASE(ERROR_OUT_OF_DATE_KHR)          VK_RESULT_CASE(ERROR_INCOMPATIBLE_DISPLAY_KHR)
	VK_RESULT_CASE(ERROR_VALIDATION_FAILED_EXT)    VK_RESULT_CASE(ERROR_INVALID_SHADER_NV)
#ifdef VK_ENABLE_BETA_EXTENSIONS
	VK_RESULT_CASE(ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR)
	VK_RESULT_CASE(ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR)
	VK_RESULT_CASE(ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR)
	VK_RESULT_CASE(ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR)
	VK_RESULT_CASE(ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR)
	VK_RESULT_CASE(ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR)
#endif
	VK_RESULT_CASE(ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
	VK_RESULT_CASE(ERROR_NOT_PERMITTED_KHR)
	VK_RESULT_CASE(ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)
	VK_RESULT_CASE(THREAD_IDLE_KHR)        VK_RESULT_CASE(THREAD_DONE_KHR)
	VK_RESULT_CASE(OPERATION_DEFERRED_KHR) VK_RESULT_CASE(OPERATION_NOT_DEFERRED_KHR)
	default: return "unknown";
	}
#undef VK_RESULT_CASE
}
