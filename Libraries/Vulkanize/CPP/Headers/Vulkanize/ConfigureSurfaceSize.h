#pragma once

namespace VKZ
{
  struct ConfigureSurfaceSize : Component
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual void on_configure();
  };
};
