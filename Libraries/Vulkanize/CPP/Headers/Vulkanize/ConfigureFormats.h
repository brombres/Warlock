#pragma once

namespace VKZ
{
  struct ConfigureFormats : Operation
  {
    Context* context;

    ConfigureFormats( Context* context );
    virtual bool configure();
  };
};
