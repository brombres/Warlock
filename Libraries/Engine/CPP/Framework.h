#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

namespace Warlock
{
  struct Renderer;

  typedef int Window;

  struct Framework
  {
    Renderer* renderer = nullptr;

    ~Framework();

    virtual void configure() {}
    virtual Window create_window();
  };
};

#endif // WARLOCK_DISPLAY
