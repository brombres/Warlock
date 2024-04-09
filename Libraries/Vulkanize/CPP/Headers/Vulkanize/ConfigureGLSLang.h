#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureGLSLang : Operation
  {
    virtual bool activate();
    virtual void deactivate();
  };
};
