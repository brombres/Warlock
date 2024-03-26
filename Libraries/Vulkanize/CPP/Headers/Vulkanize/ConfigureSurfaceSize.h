#pragma once

namespace VKZ
{
  struct ConfigureSurfaceSize : Action
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual bool on_activate();
  };
};
