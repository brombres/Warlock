#pragma once

namespace VKZ
{
  struct ConfigureSurfaceSize : Procedure
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual bool on_configure();
  };
};
