#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <vector>
#include <string>

#include "Balefire/Core/CmdData.h"
#include "Balefire/Core/RenderCmd.h"
#include "Balefire/Core/Window.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRenderContext.h"

namespace BALEFIRE
{
  typedef CmdData* (*BeginRenderHandler)(Window* window, void* app_data);
  typedef void     (*EndRenderHandler)(Window* window, void* app_data);

  struct Balefire
  {
    static Balefire* instance;

    BeginRenderHandler begin_render_handler;
    EndRenderHandler   end_render_handler;
    void*              handler_app_data;

    std::vector<Window*> windows;

    Framework* framework = nullptr;

    Balefire() { instance = this; }
    Balefire( Framework* framework );

    virtual ~Balefire();
    virtual void     configure( Framework* framework );
    virtual Window*  create_window( int index, std::string name );
    virtual bool     handle_events();
    virtual void     render();
    virtual void     set_render_handlers( BeginRenderHandler begin_render, EndRenderHandler end_render,
                                          void* app_data=nullptr );
  };
};

#endif // BALEFIRE_H
