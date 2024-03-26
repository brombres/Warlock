#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSwapchain::ConfigureSwapchain( Context* context )
  : Procedure(), context(context)
{
}

bool ConfigureSwapchain::on_configure()
{
  return true;
}

void ConfigureSwapchain::on_destroy()
{
}

