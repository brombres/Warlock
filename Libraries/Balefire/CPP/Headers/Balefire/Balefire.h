#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <vector>
#include <string>

namespace BALEFIRE
{
  typedef int  WindowID;
  typedef void (*Callback)(void* data);
};

#include "Balefire/Core/CmdData.h"
#include "Balefire/Core/RenderCmd.h"
#include "Balefire/Core/Window.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRenderContext.h"

namespace BALEFIRE
{
  struct Balefire
  {
    std::vector<Window*> windows;

    Framework* framework = nullptr;

    Balefire() {}
    Balefire( Framework* framework );

    ~Balefire();
    void     configure( Framework* framework );
    Window*  create_window( int index, std::string name );
    bool     handle_events();
    void     render( CmdData* data );
  };
};

#endif // BALEFIRE_H
