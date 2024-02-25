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

    virtual void configure( Warlock::Display* display );

    virtual Window create_window();
  };
};

#endif // WARLOCK_ENGINE
