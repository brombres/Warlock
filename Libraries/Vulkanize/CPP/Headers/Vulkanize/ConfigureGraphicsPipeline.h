#pragma once

#include <vector>
#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureGraphicsPipeline : ContextOperation<Context>
  {
    std::vector<VertexDescription*> vertex_descriptions;

    virtual ~ConfigureGraphicsPipeline();

    virtual bool activate();
    virtual void add_vertex_description( VertexDescription* vertex_description );
    virtual void deactivate();

    VkShaderModule _create_shader_module( const Byte* code, int count );
  };
};
