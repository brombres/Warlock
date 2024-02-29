#ifndef WARLOCK_RENDERER
#define WARLOCK_RENDERER

#pragma once

#include "Framework.h"

namespace Warlock
{
  struct Renderer
  {
    ~Renderer();

    virtual void configure() {}
    virtual void configure_window( Window window ) {}
  };
};

#endif // WARLOCK_RENDERER
