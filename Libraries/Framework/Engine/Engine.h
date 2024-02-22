#ifndef WARLOCK_ENGINE
#define WARLOCK_ENGINE

#pragma once

#include "Display.h"
#include "Renderer.h"

namespace Warlock
{
  struct Engine
  {
    Warlock::Display* display = nullptr;

    ~Engine();

    virtual void configure( Warlock::Display* manager );
  };
};

#endif // WARLOCK_ENGINE
