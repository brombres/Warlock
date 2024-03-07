#include "Balefire/Core/Window.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

#include <vector>
using namespace std;

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
  window->render_context->configure();
}

// https://www.reddit.com/r/vulkan/comments/zxgst4/comment/j29a1kl/?utm_source=share&utm_medium=web2x&context=3
const char* RendererVulkan::vkResult_to_c_string( VkResult result )
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
