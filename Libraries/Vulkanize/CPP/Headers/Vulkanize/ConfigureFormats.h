#pragma once

namespace VKZ
{
  struct ConfigureFormats : Procedure
  {
    Context* context;

    ConfigureFormats( Context* context );
    virtual bool on_configure();
  };
};
