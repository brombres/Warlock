#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct RenderBegin : Operation
  {
    Context* context;

    RenderBegin( Context* context );
    virtual bool execute();
  };
};
