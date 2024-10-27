#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowRenderer
  {
    Window* window   = nullptr;
    bool initialized = false;

    WindowRenderer( Window* window ) : window(window) {}
    virtual ~WindowRenderer() {}

    virtual void configure() {}
    virtual void render( unsigned char* data, int count ) {}
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_H
