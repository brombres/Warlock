#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct VertexDescription : VKZ::CustomVertexDescription<Vertex>
  {
    virtual void collect_attribute_descriptions( std::vector<VkVertexInputAttributeDescription>& list )
    {
      VKZ_VERTEX_ATTRIBUTE( Vertex, 0, position, VK_FORMAT_R32G32B32A32_SFLOAT );
      VKZ_VERTEX_ATTRIBUTE( Vertex, 1, color,    VK_FORMAT_R8G8B8A8_SRGB );
      VKZ_VERTEX_ATTRIBUTE( Vertex, 2, uv,       VK_FORMAT_R32G32_SFLOAT );
      VKZ_VERTEX_ATTRIBUTE( Vertex, 3, data,     VK_FORMAT_R32_UINT );
    }
  };
};
