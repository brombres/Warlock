#pragma once

namespace VKZ
{
  struct ConfigureQueues : Operation
  {
    Context* context;

    ConfigureQueues( Context* context );
    virtual bool activate();
  };
};
