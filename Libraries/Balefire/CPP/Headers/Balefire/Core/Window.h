#ifndef BALEFIRE_WINDOW_H
#define BALEFIRE_WINDOW_H

#pragma once

#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRendererContext.h"

typedef int WindowID;

namespace BALEFIRE
{
  struct Window : RefCounted
  {
    WindowID id = 0;
    int width;
    int height;

    Ref<WindowFrameworkContext> framework_context;
    Ref<WindowRendererContext>  renderer_context;

    Window( int width, int height ) : width(width), height(height) {}

    ~Window()
    {
      renderer_context = nullptr;
      framework_context = nullptr;
    }
  };
};

#endif // BALEFIRE_WINDOW_H
