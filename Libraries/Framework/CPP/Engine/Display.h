#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

#include "Renderer.h"

namespace Warlock
{
  typedef int Window;

  struct Display
  {
    Warlock::Renderer* renderer = nullptr;

    ~Display();

    virtual void configure() {}
    virtual Window create_window();
  };
};

#endif // WARLOCK_DISPLAY
