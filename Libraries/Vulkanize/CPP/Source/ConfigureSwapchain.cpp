#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSwapchain::ConfigureSwapchain( Context* context )
  : Procedure(), context(context)
{
}

void ConfigureSwapchain::on_configure()
{
  configured = true;
}

void ConfigureSwapchain::on_destroy()
{
}

