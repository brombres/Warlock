#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

#include "Renderer.h"
#include "Window.h"

namespace Warlock
{
  struct Display
  {
    Warlock::Renderer* renderer = nullptr;

    ~Display();

    virtual void configure() {}
    virtual Window create_window();
  };
};

#endif // WARLOCK_DISPLAY
