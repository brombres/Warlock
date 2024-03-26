#pragma once

namespace VKZ
{
  struct ConfigureSwapchain : Action
  {
    Context* context;

    ConfigureSwapchain( Context* context );
    virtual bool on_activate();
    virtual void on_deactivate();
  };
};
