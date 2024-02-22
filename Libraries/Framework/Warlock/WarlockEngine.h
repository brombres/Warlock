#ifndef WARLOCK_ENGINE
#define WARLOCK_ENGINE

#pragma once

#include "WarlockDisplayManager.h"
#include "WarlockRenderer.h"

namespace Warlock
{
  struct Engine
  {
    Warlock::DisplayManager* display_manager = nullptr;

    ~Engine();

    virtual void configure( Warlock::DisplayManager* manager );
  };
};

#endif // WARLOCK_ENGINE
