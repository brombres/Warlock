#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
using namespace VULKANIZE;

VkzContext::VkzContext( VkSurfaceKHR surface ) : surface(surface)
{
}

VkzContext::~VkzContext()
{
  destroy();
}

bool VkzContext::destroy()
{
  if (surface)
  {
    vkb::destroy_surface( vulkanize.vulkan_instance, surface );
    surface = nullptr;
  }

  if (configured)
  {
    configured = false;
    vkb::destroy_device( device );
  }

  return false;
}

bool VkzContext::configure()
{
  _configure_device();
  configured = true;
  return true;
}

bool VkzContext::_configure_device()
{
	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{};
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

	vkb::PhysicalDeviceSelector selector{ vulkanize.vulkan_instance };
  VKB_SET( physical_device,
    selector
      .set_minimum_version(1,2)
      //.set_required_features_13(features)
      .set_required_features_12( features12 )
      .set_surface( surface )
      .select(),
    "selecting physical device",
    return destroy()
  );

  VKB_SET( device, vkb::DeviceBuilder{physical_device}.build(), "building device", return destroy() );
  device_dispatch = device.make_table();
  return true;
}
