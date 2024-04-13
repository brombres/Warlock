#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureShaders::ConfigureShaders( Context* context ) : context(context)
{
}

bool ConfigureShaders::activate()
{
  return true;
}

void ConfigureShaders::deactivate()
{
}

