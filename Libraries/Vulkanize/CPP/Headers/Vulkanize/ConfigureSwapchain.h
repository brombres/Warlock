#pragma once

namespace VKZ
{
  struct ConfigureSwapchain : Action
  {
    Context* context;
    bool     reconfiguring = false;

    ConfigureSwapchain( Context* context );
    virtual bool on_configure();
    virtual void on_deactivate();
    virtual void on_surface_lost();
  };
};
