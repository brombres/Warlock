#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureStandardVertexBuffer : Operation
  {
    Context* context;

    ConfigureStandardVertexBuffer( Context* context ) : context(context) {}
    virtual bool activate();
    virtual void deactivate();
  };
};
