#ifndef WARLOCK_RENDERER
#define WARLOCK_RENDERER

#pragma once

#include "Display.h"

namespace Warlock
{
  struct Renderer
  {
    ~Renderer();

    virtual void configure( Display* display ) {}
  };
};

#endif // WARLOCK_RENDERER
