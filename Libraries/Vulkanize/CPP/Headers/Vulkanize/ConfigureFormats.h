#pragma once

namespace VKZ
{
  struct ConfigureFormats : Procedure
  {
    Context* context;

    ConfigureFormats( Context* context );
    virtual void on_configure();
  };
};
