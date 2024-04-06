#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureCommandBuffers : Operation
  {
    Context* context;

    ConfigureCommandBuffers( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
