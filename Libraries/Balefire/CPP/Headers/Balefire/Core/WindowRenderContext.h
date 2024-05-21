#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowRenderContext
  {
    Window* window   = nullptr;
    bool initialized = false;

    WindowRenderContext( Window* window ) : window(window) {}
    virtual ~WindowRenderContext() {}

    virtual void configure() {}
    virtual void render( RenderCmdData* data ) {}
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_H
