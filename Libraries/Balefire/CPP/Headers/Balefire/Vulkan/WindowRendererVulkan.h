#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct WindowRendererVulkan : WindowRenderer
  {
    // PROPERTIES
    RendererVulkan* render_api;
    VulkanContext*  context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    std::vector<Vertex>    vertices;
    std::vector<RenderCmd> render_commands;

    glm::mat4x4              projection_transform;
    glm::mat4x4              transform;
    glm::mat4x4              world_transform;
    glm::mat4x4              view_transform;
    glm::mat4x4              object_transform;
    std::vector<glm::mat4x4> view_transforms;
    std::vector<glm::mat4x4> object_transforms;

    // CONSTRUCTORS
    WindowRendererVulkan( Window* window, RendererVulkan* render_api )
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
