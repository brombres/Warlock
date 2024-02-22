#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

#include "RefCounted.h"
#include "Renderer.h"

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
