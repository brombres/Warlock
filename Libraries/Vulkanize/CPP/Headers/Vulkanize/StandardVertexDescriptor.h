#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct StandardVertexDescriptor : VertexDescriptor<StandardVertex>
  {
    virtual std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions();
  };
};
