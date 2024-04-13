#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureShaders : Operation
  {
    Context* context;

    ConfigureShaders( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
