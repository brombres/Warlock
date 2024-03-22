#pragma once

#include <vulkan/vulkan.h>

namespace VULKANIZE
{
  struct Context
  {
    VkSurfaceKHR        surface = nullptr;

    bool                configured = false;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    Context( VkSurfaceKHR surface );
    ~Context();
    bool destroy();

    bool configure();
    bool _configure_device();
  };
};
