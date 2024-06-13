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
    int  index = 0;
    int  width, height;
    int  pixel_width, pixel_height;
    bool rendering_paused = false;

    WindowFrameworkContext* framework_context = nullptr;
    WindowRenderContext*    render_context = nullptr;

    Window( Framework* framework, int index, int width, int height ) : framework(framework),
        index(index), width(width), height(height), pixel_width(width), pixel_height(height) {}

    virtual ~Window();

    void render( const char* render_data, int count );
    void update_pixel_size();
  };
};

#endif // BALEFIRE_WINDOW_H
