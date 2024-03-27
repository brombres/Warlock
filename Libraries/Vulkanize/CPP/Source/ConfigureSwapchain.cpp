#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSwapchain::ConfigureSwapchain( Context* context )
  : Action(), context(context)
{
}

bool ConfigureSwapchain::on_activate()
{
	vkb::SwapchainBuilder swapchain_builder{ context->device };
	auto swapchain_build_result = swapchain_builder
    .set_desired_format( context->swapchain_surface_format )
    //.set_desired_format( VK_FORMAT_B8G8R8A8_UNORM )
    //.set_desired_format( {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR} )
		//.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( context->surface_size.width, context->surface_size.height )
    .set_old_swapchain( context->swapchain )
		.build();
  vkb::destroy_swapchain( context->swapchain );
  context->swapchain = swapchain_build_result.value();

  context->swapchain_images = context->swapchain.get_images().value();
  context->swapchain_image_views = context->swapchain.get_image_views().value();

  return true;
}

void ConfigureSwapchain::on_deactivate()
{
}

