#ifndef WARLOCK_DISPLAY
#define WARLOCK_DISPLAY

#pragma once

namespace Warlock
{
  struct Renderer;

  typedef int Window;

  struct Display
  {
    Renderer* renderer = nullptr;

    ~Display();

    virtual void configure() {}
    virtual Window create_window();
  };
};

#endif // WARLOCK_DISPLAY
