#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>

#include "Balefire/Vulkan/RenderAPIVulkan.h"

namespace BALEFIRE
{
  struct WindowRendererVulkan : WindowRenderer
  {
    // PROPERTIES
    RenderAPIVulkan* render_api;
    VulkanContext*  context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    // CONSTRUCTORS
    WindowRendererVulkan( Window* window, RenderAPIVulkan* render_api )
      : WindowRenderer(window), render_api(render_api) {}
    virtual ~WindowRendererVulkan();

    // METHODS
    virtual void configure();
    virtual void configure( VkSurfaceKHR surface );

    virtual void draw_line( double x1, double y1, double x2, double y2, Color color );
    virtual void flush();

    virtual void render( unsigned char* data, int count );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
