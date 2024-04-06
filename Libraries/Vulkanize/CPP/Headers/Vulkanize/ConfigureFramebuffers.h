#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureFramebuffers : Operation
  {
    Context* context;

    ConfigureFramebuffers( Context* context );
    virtual bool activate();
    virtual void deactivate();
  };
};
