#pragma once

#include <string>

namespace VKZ
{
  struct ConfigureSurfaceSize : Operation
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual bool on_event( std::string event_type );
    virtual bool configure();
  };
};
