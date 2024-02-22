#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

#include "SmartPointer.h"
#include "WarlockRenderer.h"

namespace Warlock
{
  struct Display
  {
    Warlock::Renderer* renderer = nullptr;

    ~Display();

    virtual void configure() {}
  };
};

#endif // WARLOCK_DISPLAY
