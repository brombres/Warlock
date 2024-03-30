#pragma once

#include <string>

namespace VKZ
{
  struct ConfigureSwapchain : Operation
  {
    Context* context;
    bool     reconfiguring = false;

    ConfigureSwapchain( Context* context );
    virtual bool on( std::string event_type );
    virtual bool on_configure();
    virtual void on_deactivate();
  };
};
