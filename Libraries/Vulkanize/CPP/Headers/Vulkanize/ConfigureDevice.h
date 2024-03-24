#pragma once

namespace VKZ
{
  struct ConfigureDevice : Component
  {
    Context* context;
    int major_version;
    int minor_version;

    ConfigureDevice( Context* context, int major_version=1, int minor_version=2 );
    virtual void on_configure();
    virtual void on_destroy();

    virtual const char* phase() { return VKZ_CONFIGURE_DEVICE; }
  };
};
