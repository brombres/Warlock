#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct RenderEnd : Operation
  {
    Context* context;

    RenderEnd( Context* context );
    virtual bool execute();
  };
};
