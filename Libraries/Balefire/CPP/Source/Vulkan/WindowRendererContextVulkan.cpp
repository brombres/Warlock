#include "Balefire/Vulkan/WindowRendererContextVulkan.h"
using namespace BALEFIRE;

WindowRendererContextVulkan::~WindowRendererContextVulkan()
{
  if (initialized)
  {
    initialized = false;

		vkDestroySwapchainKHR( device, swapchain, nullptr );

		for (int i=0; i<swapchain_image_views.size(); ++i)
    {
			vkDestroyImageView( device, swapchain_image_views[i], nullptr );
		}

		vkDestroyDevice( device, nullptr );
		vkDestroySurfaceKHR( renderer->vulkan_instance, surface, nullptr );
  }
}
