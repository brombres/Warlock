#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureFences : Operation
  {
    Context* context;

    ConfigureFences( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
