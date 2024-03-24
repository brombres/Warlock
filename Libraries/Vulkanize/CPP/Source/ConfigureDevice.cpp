#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VULKANIZE;

ConfigureDevice::ConfigureDevice( Context* context, int major_version, int minor_version )
  : Component(), context(context), major_version(major_version), minor_version(minor_version)
{
}

void ConfigureDevice::on_configure()
{
  //vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{ vulkanize.vulkan_instance };
  VKZ_SET( context->physical_device,
    selector
      .set_minimum_version(major_version,minor_version)
      //.set_required_features_13(features)
      .set_required_features_12( features12 )
      .set_surface( context->surface )
      .select(),
    "selecting physical device",
    return
  );

  VKZ_SET(
    context->device,
    vkb::DeviceBuilder{context->physical_device}.build(),
    "building device",
    return
  );

  context->device_dispatch = context->device.make_table();

  configured = true;
}

void ConfigureDevice::on_destroy()
{
  vkb::destroy_device( context->device );
}

