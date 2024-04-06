#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Balefire/Core/WindowRenderContext.h"
#include "Balefire/Vulkan/RendererVulkan.h"

#include "Vulkanize/Vulkanize.h"


namespace BALEFIRE
{
  struct WindowRenderContextVulkan : WindowRenderContext
  {
    // PROPERTIES
    RendererVulkan* renderer;
    VKZ::Context*   context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    //size_t current_frame = 0;
    //int frame_count = 0;  // FIXME

    // CONSTRUCTORS
    WindowRenderContextVulkan( Window* window, RendererVulkan* renderer )
      : WindowRenderContext(window), renderer(renderer) {}
    virtual ~WindowRenderContextVulkan();

    // METHODS
    virtual void configure();
    virtual void configure( VkSurfaceKHR surface );
    virtual void render();
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
