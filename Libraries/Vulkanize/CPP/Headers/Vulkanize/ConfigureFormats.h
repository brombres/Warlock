#pragma once

namespace VKZ
{
  struct ConfigureFormats : Action
  {
    Context* context;

    ConfigureFormats( Context* context );
    virtual bool on_activate();
  };
};
