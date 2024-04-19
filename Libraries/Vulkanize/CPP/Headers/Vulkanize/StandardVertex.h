#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct StandardVertex : Vertex
  {
    struct { float x, y, z; } position;
    uint32_t rgba;

    virtual VkVertexInputBindingDescription get_binding_description();
    virtual std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions();
  };
};
