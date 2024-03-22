#pragma once

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Vulkanize/ExtendedContext.h"

namespace VULKANIZE
{
  struct StandardContext : ExtendedContext<StandardContext>
  {
    StandardContext( VkSurfaceKHR surface ) : ExtendedContext<StandardContext>(surface) {}
  };
};
