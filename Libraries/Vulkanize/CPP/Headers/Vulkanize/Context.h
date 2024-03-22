#pragma once

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

namespace VULKANIZE
{
  struct Context
  {
    VkSurfaceKHR        surface;

    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    Context( VkSurfaceKHR surface ) : surface(surface) {}
    virtual ~Context();

    virtual bool configure() = 0;
  };
};
