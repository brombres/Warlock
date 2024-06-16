#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct VulkanContext : VKZ::Context
  {
    // PROPERTIES
    Window*          window;

    VKZ::Descriptors descriptors;

    VKZ::GraphicsPipeline gfx_line_list_color;
    VKZ::GraphicsPipeline gfx_triangle_list_color;
    VKZ::GraphicsPipeline gfx_triangle_list_texture;

    std::vector<VKZ::Image*> textures;

    VKZ::Image   test_image;
    VKZ::Sampler test_sampler;

    VKZ::UniformBufferDescriptor<Vec4>*  fill_color;
    VKZ::CombinedImageSamplerDescriptor* image_sampler;

    // METHODS
    VulkanContext( Window* window, VkSurfaceKHR surface ) : VKZ::Context(surface), window(window) {}

    void configure_operations() override;
    void on_surface_size_change( int width, int height ) override;
  };
};
