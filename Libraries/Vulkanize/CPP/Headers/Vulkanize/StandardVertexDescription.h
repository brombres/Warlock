#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct StandardVertexDescription : CustomVertexDescription<StandardVertex>
  {
    virtual void collect_attribute_descriptions( std::vector<VkVertexInputAttributeDescription>& list );
  };
};
