#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSurfaceSize::ConfigureSurfaceSize( Context* context )
  : Operation(), context(context)
{
}

bool ConfigureSurfaceSize::on( std::string event_type )
{
  if (event_type == "surface_lost")
  {
    configured = false;
  }
  return true;
}

bool ConfigureSurfaceSize::on_configure()
{
  VkSurfaceCapabilitiesKHR surface_capabilities;

  vulkanize.instance_dispatch.getPhysicalDeviceSurfaceCapabilitiesKHR(
    context->physical_device,
    context->surface,
    &surface_capabilities
  );

  int width = (int)surface_capabilities.currentExtent.width;
  int height = (int)surface_capabilities.currentExtent.height;

  context->surface_size.width = width;
  context->surface_size.height = height;

  return true;
}

