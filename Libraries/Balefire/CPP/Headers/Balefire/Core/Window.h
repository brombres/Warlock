#ifndef BALEFIRE_WINDOW_H
#define BALEFIRE_WINDOW_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Framework;
  struct WindowFrameworkContext;
  struct WindowRenderContext;

  struct Window
  {
    Framework* framework;
    WindowID   id = 0;
    int width, height;
    int pixel_width, pixel_height;

    WindowFrameworkContext* framework_context = nullptr;
    WindowRenderContext*    render_context = nullptr;

    Window( Framework* framework, int width, int height ) : framework(framework),
        width(width), height(height), pixel_width(width), pixel_height(height) {}

    virtual ~Window();

    void render();
    void update_pixel_size();
  };
};

#endif // BALEFIRE_WINDOW_H
