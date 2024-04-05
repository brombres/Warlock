#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureRenderPasses : Operation
  {
    Context* context;

    ConfigureRenderPasses( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
