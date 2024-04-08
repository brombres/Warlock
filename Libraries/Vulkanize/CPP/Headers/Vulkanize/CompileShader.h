#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct CompileShader : Operation
  {
    Context* context;

    CompileShader( Context* context );
    virtual bool activate();
    virtual void deactivate();
    virtual bool execute();
  };
};
