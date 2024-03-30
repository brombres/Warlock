#pragma once

#include <string>

namespace VKZ
{
  struct ConfigureSurfaceSize : Operation
  {
    Context* context;

    ConfigureSurfaceSize( Context* context );
    virtual bool on( std::string event_type );
    virtual bool on_configure();
  };
};
