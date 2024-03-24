#pragma once

namespace VULKANIZE
{
  struct ConfigureDevice : Component
  {
    Context* context;
    int major_version;
    int minor_version;

    ConfigureDevice( Context* context, int major_version=1, int minor_version=2 );
    virtual bool configure();
    virtual bool destroy();
  };
};
