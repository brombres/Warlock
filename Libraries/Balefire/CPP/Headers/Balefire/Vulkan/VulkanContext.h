#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct VulkanContext : VKZ::Context
  {
    // PROPERTIES
    Window*          window;

    VKZ::OldDescriptors descriptors;

    VKZ::GraphicsPipeline gfx_line_list_color;
    VKZ::GraphicsPipeline gfx_triangle_list_color;
    VKZ::GraphicsPipeline gfx_triangle_list_texture;

    VKZ::Ref<VKZ::Shader> color_shader;
    VKZ::Ref<VKZ::Shader> texture_shader;

    VKZ::Ref<VKZ::Material> color_line_list_material;
    VKZ::Ref<VKZ::Material> color_triangle_list_material;

    std::vector<VKZ::Ref<VKZ::Image>>    textures;
    std::vector<VKZ::Ref<VKZ::Material>> materials;

    VKZ::Sampler test_sampler;

    VKZ::OldUniformBufferDescriptor<Vec4>*  fill_color;
    VKZ::OldCombinedImageSamplerDescriptor* image_sampler;

    // METHODS
    VulkanContext( Window* window, VkSurfaceKHR surface ) : VKZ::Context(surface), window(window) {}

    void configure_operations() override;
    void on_surface_size_change( int width, int height ) override;
  };
};
