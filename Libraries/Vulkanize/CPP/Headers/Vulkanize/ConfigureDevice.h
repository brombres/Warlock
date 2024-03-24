#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VULKANIZE
{
  struct ConfigureDevice : Component
  {
    Context* context;

    ConfigureDevice( Context* context ) : Component(), context(context) {}
    virtual bool configure();
    virtual bool destroy();
  };
};
