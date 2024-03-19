#pragma once

#include <vulkan/vulkan.h>

namespace VULKANIZE
{
  struct VkzContext
  {
    VkSurfaceKHR        surface = nullptr;

    bool                configured = false;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    VkzContext( VkSurfaceKHR surface );
    ~VkzContext();
    bool destroy();

    bool configure();
    bool _configure_device();
  };
};
