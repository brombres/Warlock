#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct VulkanContext : VKZ::Context
  {
    // PROPERTIES
    Window*          window;

    std::vector<VKZ::Buffer> vertex_buffers;
    std::vector<VKZ::Buffer> staging_buffers;
    VKZ::Buffer*             vertex_buffer;
    VKZ::Buffer*             staging_buffer;

    VKZ::Ref<VKZ::Shader> color_vertex_shader;
    VKZ::Ref<VKZ::Shader> color_fragment_shader;
    VKZ::Ref<VKZ::Shader> texture_vertex_shader;
    VKZ::Ref<VKZ::Shader> texture_fragment_shader;

    VKZ::Ref<VKZ::Material> color_line_list_material;
    VKZ::Ref<VKZ::Material> color_triangle_list_material;

    std::vector<VKZ::Ref<VKZ::Image>>       textures;
    std::vector<VKZ::Ref<VKZ::Material>>    materials;
    std::vector<VKZ::Ref<VKZ::Shader>>      shaders;

    // METHODS
    VulkanContext( Window* window, VkSurfaceKHR surface ) : VKZ::Context(surface), window(window) {}

    void configure_operations() override;
    void on_surface_size_change( int width, int height ) override;
  };
};
