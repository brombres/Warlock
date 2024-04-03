#pragma once

#include <string>

namespace VKZ
{
  struct ConfigureSwapchain : Operation
  {
    Context* context;
    bool     reconfiguring = false;

    ConfigureSwapchain( Context* context );
    virtual bool activate();
    virtual void deactivate();
    virtual bool on_event( std::string event_type );
  };
};
