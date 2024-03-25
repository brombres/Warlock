#pragma once

namespace VKZ
{
  struct ConfigureSwapchain : Procedure
  {
    Context* context;

    ConfigureSwapchain( Context* context );
    virtual void on_configure();
    virtual void on_destroy();
  };
};
