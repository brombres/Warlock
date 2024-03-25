#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureFormats::ConfigureFormats( Context* context )
  : Procedure(), context(context)
{
}

void ConfigureFormats::on_configure()
{
  context->swapchain_surface_format = { VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
  configured = true;
}

