#pragma once

namespace VKZ
{
  struct ConfigureSwapchain : Component
  {
    Context* context;

    ConfigureSwapchain( Context* context );
    virtual const char* configuration_step() { return VKZ_CONFIGURE_SWAPCHAIN; }
    virtual void on_configure();
    virtual void on_destroy();
  };
};
