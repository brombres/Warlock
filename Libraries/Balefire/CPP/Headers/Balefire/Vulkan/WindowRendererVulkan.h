#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>

#include "Balefire/Vulkan/GraphicsAPIVulkan.h"

namespace BALEFIRE
{
  struct WindowRendererVulkan : BufferedVertexWindowRenderer
  {
    // PROPERTIES
    VulkanContext*  context = nullptr;
    VkSurfaceKHR    surface = nullptr;

    // CONSTRUCTORS
    WindowRendererVulkan( Window* window, GraphicsAPIVulkan* graphics_api );
    virtual ~WindowRendererVulkan();

    // METHODS
    virtual void configure();
    virtual void configure( VkSurfaceKHR surface );

    virtual Ref<Shader> create_shader( ShaderStage stage, std::string filename, std::string source,
                                       std::string main_function_name="main" );

    virtual void render( unsigned char* data, int count );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
