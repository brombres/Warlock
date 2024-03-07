#ifndef BALEFIRE_WINDOW_RENDERER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDERER_CONTEXT_H

#pragma once

#include "Balefire/Core/RefCounted.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowRendererContext : RefCounted
  {
    Window* window;
    bool initialized = false;

    WindowRendererContext( Window* window ) : window(window) {}

    virtual void configure() {}
    virtual void render() {}
  };
};

#endif // BALEFIRE_WINDOW_RENDERER_CONTEXT_H
