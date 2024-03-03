#ifndef BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H

#pragma once

#include "Balefire/Core/WindowRendererContext.h"

namespace BALEFIRE
{
  struct WindowRendererContextVulkan : WindowRendererContext
  {
    VkPhysicalDevice gpu;
    VkDevice         device;
    VkSurfaceKHR     surface;
  };
};

#endif // BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H
