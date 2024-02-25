#ifndef WARLOCK_RENDERER
#define WARLOCK_RENDERER

#pragma once

#include "Framework.h"

namespace Warlock
{
  struct Renderer
  {
    ~Renderer();

    virtual void configure( Framework* display ) {}
  };
};

#endif // WARLOCK_RENDERER
