#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <vector>
#include <string>

#include "Balefire/Core/DataReader.h"
#include "Balefire/Core/RenderCmd.h"
#include "Balefire/Core/Window.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRenderContext.h"

namespace BALEFIRE
{
  typedef bool (*BeginRenderHandler)(Window* window, void* app_data, unsigned char** render_data, int* count );
  typedef void (*EndRenderHandler)(Window* window, void* app_data);

  const int VERTEX_PROPERTY_COUNT = 7;

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

#define BALEFIRE_LOG_ERROR( message ) \
  fprintf( stderr, "[Balefire] %s\n", message );

#define BALEFIRE_LOG_ERROR_WITH_INT( message, value ) \
  {                                                   \
    char buffer[120];                                 \
    snprintf( buffer, 120, message, value );          \
    BALEFIRE_LOG_ERROR( buffer );                     \
  }

#endif // BALEFIRE_H
