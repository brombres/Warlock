#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureDepthStencil : Operation
  {
    Context* context;

    ConfigureDepthStencil( Context* context );
    virtual bool configure();
    virtual void deactivate();
    virtual bool _find_supported_depth_format( VkFormat* depth_format );
  };
};
