#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VULKANIZE
{
  struct StandardConfigureDeviceComponent : Component
  {
    Context* context;

    StandardConfigureDeviceComponent( Context* context ) : Component(), context(context) {}
    virtual bool configure();
    virtual bool destroy();
  };
};
