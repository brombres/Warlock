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

    virtual int  _add_verticles( RenderCmdData* data, int i, std::vector<VKZ::StandardVertex>& vertices );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
