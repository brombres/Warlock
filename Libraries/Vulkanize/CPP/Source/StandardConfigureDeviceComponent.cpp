#include "VkBootstrap.h"
#include "Vulkanize/StandardConfigureDeviceComponent.h"
using namespace VULKANIZE;

bool StandardConfigureDeviceComponent::configure()
{
  //vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{ vulkanize.vulkan_instance };
  VKZ_SET( context->physical_device,
    selector
      .set_minimum_version(1,3)
      //.set_required_features_13(features)
      .set_required_features_12( features12 )
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

  configured = true;
  return true;
}

bool StandardConfigureDeviceComponent::destroy()
{
  vkb::destroy_device( context->device );

  configured = false;
  return false;
}

