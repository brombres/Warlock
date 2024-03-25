#pragma once

namespace VKZ
{
  struct ConfigureFormats : Component
  {
    Context* context;

    ConfigureFormats( Context* context );
    virtual void on_configure();
  };
};
