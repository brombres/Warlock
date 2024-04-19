#pragma once

#include <vector>
#include "Vulkanize/Vulkanize.h"

#define VKZ_VERTEX_ATTRIBUTE( _vertex_type, _location, _name, _format ) \
  descriptions.push_back(                                               \
    VkVertexInputAttributeDescription                                   \
    {                                                                   \
      .location = _location,                                            \
      .format   = _format,                                              \
      .offset   = offsetof( _vertex_type, _name);                       \
    };                                                                  \
  );

namespace VKZ
{
  struct Vertex
  {
    // Return 'true' if there is one vertex per instance rather than one vertex per vertex.
    virtual bool per_instance() { return false; }

    // For extended Vertex type VX, return sizeof(VX).
    virtual size_t size() = 0;

    // Typically no need to overload this.
    virtual VkVertexInputBindingDescription get_binding_description();

    // Overload this method in your extended Vertex. See StandardVertex::get_attribute_descriptions()
    // for an example.
    virtual std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions() = 0;
  };

};
