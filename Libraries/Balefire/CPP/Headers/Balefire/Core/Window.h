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
  struct Window : RefCounted
  {
    WindowID id = 0;
    int width, height;
    int pixel_width, pixel_height;

    Ref<WindowFrameworkContext> framework_context;
    Ref<WindowRenderContext>  render_context;

    Window( int width, int height ) : width(width), height(height), pixel_width(width), pixel_height(height) {}

    ~Window()
    {
      render_context = nullptr;
      framework_context = nullptr;
    }

    void render();
  };
};

#endif // BALEFIRE_WINDOW_H
