#include "Balefire/Vulkan/WindowRendererContextVulkan.h"
using namespace BALEFIRE;

WindowRendererContextVulkan::~WindowRendererContextVulkan()
{
  if (initialized)
  {
    initialized = false;

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
