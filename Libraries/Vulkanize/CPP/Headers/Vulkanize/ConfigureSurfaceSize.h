#pragma once

#include <string>

namespace VKZ
{
  struct ConfigureSurfaceSize : Operation
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual bool activate();
  };
};
