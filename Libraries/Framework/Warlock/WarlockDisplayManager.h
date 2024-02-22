#ifndef WARLOCK_DISPLAY_MANAGER
#define WARLOCK_DISPLAY_MANAGER

#pragma once

#include "WarlockRenderer.h"

namespace Warlock
{
  struct DisplayManager
  {
    Warlock::Renderer* renderer = nullptr;

    ~DisplayManager();

    virtual void configure() {}
  };
};

#endif // WARLOCK_DISPLAY_MANAGER
