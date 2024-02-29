#ifndef WARLOCK_ENGINE
#define WARLOCK_ENGINE

#pragma once

#include "Framework.h"
#include "Renderer.h"

namespace Warlock
{
  struct Engine
  {
    Warlock::Framework* display = nullptr;

    ~Engine();

    virtual void configure( Warlock::Framework* display );

    virtual Window create_window();
  };
};

#endif // WARLOCK_ENGINE
