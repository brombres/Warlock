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

    virtual void draw_line( double x1, double y1, double x2, double y2, Color color ) = 0;

    virtual void render( unsigned char* data, int count ) {}
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_H
