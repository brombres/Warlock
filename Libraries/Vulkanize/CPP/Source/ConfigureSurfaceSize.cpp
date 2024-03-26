#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSurfaceSize::ConfigureSurfaceSize( Context* context )
  : Procedure(), context(context)
{
}

void ConfigureSurfaceSize::on_configure()
{
  VkSurfaceCapabilitiesKHR surface_capabilities;

  vulkanize.instance_dispatch.getPhysicalDeviceSurfaceCapabilitiesKHR(
    context->physical_device,
    context->surface,
    &surface_capabilities
  );

  int width = (int)surface_capabilities.currentExtent.width;
  int height = (int)surface_capabilities.currentExtent.height;

  printf( "SURFACE SIZE:%dx%d\n", width, height );

  //width = BFCLAMP( width, surface_capabilities.minImageExtent.width, surface_capabilities.maxImageExtent.width );
  //height = BFCLAMP( height, surface_capabilities.minImageExtent.height, surface_capabilities.maxImageExtent.height );

  context->surface_size.width = width;
  context->surface_size.height = height;

  configured = true;
}

