#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <string>

namespace BALEFIRE
{
  typedef int  WindowID;
  typedef void (*Callback)(void* data);
};

#include "Balefire/Core/Window.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/ResourceBank.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRenderContext.h"

namespace BALEFIRE
{
  struct Balefire
  {
    void*    callback_data   = nullptr;
    Callback on_render_begin = nullptr;
    Callback on_render       = nullptr;
    Callback on_render_end   = nullptr;

    ResourceBank<WindowID,Window*> windows;

    Framework* framework = nullptr;

    Balefire() {}
    Balefire( Framework* framework );

    ~Balefire();
    void     configure( Framework* framework );
    WindowID create_window( std::string name );
    void     render();
  };
};

#endif // BALEFIRE_H
