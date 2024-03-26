#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSwapchain::ConfigureSwapchain( Context* context )
  : Action(), context(context)
{
}

bool ConfigureSwapchain::on_activate()
{
  return true;
}

void ConfigureSwapchain::on_deactivate()
{
}

