#ifndef BALEFIRE_WINDOW_H
#define BALEFIRE_WINDOW_H

#pragma once

#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRenderContext.h"

typedef int WindowID;

namespace BALEFIRE
{
  struct Framework;

  struct Window : RefCounted
  {
    Framework* framework;
    WindowID   id = 0;
    int width, height;
    int pixel_width, pixel_height;

    Ref<WindowFrameworkContext> framework_context;
    Ref<WindowRenderContext>  render_context;

    Window( Framework* framework, int width, int height ) : framework(framework),
        width(width), height(height), pixel_width(width), pixel_height(height) {}

    ~Window()
    {
      render_context = nullptr;
      framework_context = nullptr;
    }

    void render();
    void update_pixel_size();
  };
};

#endif // BALEFIRE_WINDOW_H
