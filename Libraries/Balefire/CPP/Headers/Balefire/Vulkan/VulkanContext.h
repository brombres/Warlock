#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct VulkanContext : VKZ::Context
  {
    // PROPERTIES
    VKZ::Descriptors      descriptors;

    VKZ::GraphicsPipeline gfx_line_list_color;
    VKZ::GraphicsPipeline gfx_triangle_list_color;

    VKZ::Image   test_image;
    VKZ::Sampler test_sampler;

    VKZ::UniformBufferDescriptor<Vec4>*  fill_color;
    VKZ::CombinedImageSamplerDescriptor* image_sampler;

    // METHODS
    VulkanContext( VkSurfaceKHR surface ) : VKZ::Context(surface) {}

    virtual void configure_operations() override;
  };
};
