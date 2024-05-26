#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct WindowRenderContextVulkan : WindowRenderContext
  {
    // PROPERTIES
    RendererVulkan* renderer;
    VulkanContext*  context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    // CONSTRUCTORS
    WindowRenderContextVulkan( Window* window, RendererVulkan* renderer )
      : WindowRenderContext(window), renderer(renderer) {}
    virtual ~WindowRenderContextVulkan();

    // METHODS
    virtual void configure();
    virtual void configure( VkSurfaceKHR surface );
    virtual void render( RenderCmdData* data );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
