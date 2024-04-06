#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureGraphicsPipeline : Operation
  {
    Context* context;

    ConfigureGraphicsPipeline( Context* context );
    virtual bool activate();
    virtual void deactivate();

    VkShaderModule _create_shader_module( const Byte* code, int count );
  };
};
