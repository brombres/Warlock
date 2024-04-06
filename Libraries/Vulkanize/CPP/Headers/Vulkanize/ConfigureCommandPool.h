#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureCommandPool : Operation
  {
    Context* context;

    ConfigureCommandPool( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
