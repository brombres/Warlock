#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VULKANIZE;

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
  // Set up default configuration steps
  std::vector<std::string> steps;
  steps.push_back( VKZ_CONFIGURE_DEVICE );
  steps.push_back( VKZ_CONFIGURE_SWAPCHAIN );
  steps.push_back( VKZ_CONFIGURE_QUEUES );
  steps.push_back( VKZ_CONFIGURE_DEPTH_STENCIL );
  steps.push_back( VKZ_CONFIGURE_RENDER_PASS );
  steps.push_back( VKZ_CONFIGURE_GRAPHICS_PIPELINES );
  steps.push_back( VKZ_CONFIGURE_FRAMEBUFFERS );
  steps.push_back( VKZ_CONFIGURE_COMMAND_POOL );
  steps.push_back( VKZ_CONFIGURE_COMMAND_BUFFERS );
  steps.push_back( VKZ_CONFIGURE_SEMAPHORES );
  steps.push_back( VKZ_CONFIGURE_FENCES );
  set_configuration_steps( steps );
}

Context::~Context()
{
  destroy();
  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

bool Context::configure()
{
  _configure_device();
  configured = true;
  return true;
}

bool Context::_configure_device()
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
bool Context::destroy()
{
  if (configured)
  {
    configured = false;
    vkb::destroy_device( device );
  }

  return false;
}

void Context::set_configuration_steps( std::vector<std::string>& steps )
{
  configuration_steps.clear();
  for (auto step : steps) configuration_steps.push_back( step );
}
