#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct WindowRendererVulkan : WindowRenderer
  {
    // PROPERTIES
    RendererVulkan* render_api;
    VulkanContext*  context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    std::vector<Vertex> vertices;

    // CONSTRUCTORS
    WindowRendererVulkan( Window* window, RendererVulkan* render_api )
      : WindowRenderer(window), render_api(render_api) {}
    virtual ~WindowRendererVulkan();

    // METHODS
    virtual void configure();
    virtual void configure( VkSurfaceKHR surface );
    virtual void render( unsigned char* data, int count );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
