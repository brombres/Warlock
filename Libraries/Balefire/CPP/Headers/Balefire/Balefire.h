#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <string>

namespace BALEFIRE
{
  typedef int WindowID;
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
