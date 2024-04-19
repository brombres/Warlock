#pragma once

#include <vector>
#include "Vulkanize/Vulkanize.h"

// .binding will be set during graphics pipeline configuration
#define VKZ_VERTEX_ATTRIBUTE( _vertex_type, _location, _name, _format ) \
  descriptions.push_back(                                               \
    VkVertexInputAttributeDescription                                   \
    {                                                                   \
      .location = _location,                                            \
      .format   = _format,                                              \
      .offset   = offsetof( _vertex_type, _name)                        \
    }                                                                   \
  );

namespace VKZ
{
  template <typename VertexType>
  struct VertexDescriptor
  {
    // Return 'true' if there is one vertex per instance rather than one vertex per vertex.
    virtual bool per_instance() { return false; }

    // Typically no need to overload this.
    virtual VkVertexInputBindingDescription get_binding_description()
    {
      VkVertexInputBindingDescription description = {};
      // description.binding is set during graphics pipeline construction.
      description.stride = sizeof(VertexType);
      description.inputRate = per_instance() ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;
      return description;
    }

    // Overload this method in your extended VertexDescriptor.
    //
    // EXAMPLE
    //   std::vector<VkVertexInputAttributeDescription> descriptions;
    //   VKZ_VERTEX_ATTRIBUTE( StandardVertex, 0, position, VK_FORMAT_R32G32B32_SFLOAT );
    //   VKZ_VERTEX_ATTRIBUTE( StandardVertex, 1, rgba,     VK_FORMAT_R8G8B8A8_SRGB );
    //   return descriptions;
    virtual std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions() = 0;
  };
};
