#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureDevice::ConfigureDevice( Context* context, int major_version, int minor_version )
  : Operation(), context(context), major_version(major_version), minor_version(minor_version)
{
}

bool ConfigureDevice::on_configure()
{
  //features12.bufferDeviceAddress = true;
  //features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{ vulkanize.vulkan_instance };

  VKZ_SET( context->physical_device,
    selector
      .set_minimum_version( major_version, minor_version )
      .set_required_features( required_features )
      .set_required_features_11( required_features_v1_1 )
      .set_required_features_12( required_features_v1_2 )
      .set_required_features_13( required_features_v1_3 )
      .set_surface( context->surface )
      .select(),
    "selecting physical device",
    return false
  );

  VKZ_SET(
    context->device,
    vkb::DeviceBuilder{context->physical_device}.build(),
    "building device",
    return false
  );

  context->device_dispatch = context->device.make_table();

  return true;
}

void ConfigureDevice::on_deactivate()
{
  vkb::destroy_device( context->device );
}

