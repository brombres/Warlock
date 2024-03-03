#ifndef BALEFIRE_RENDERER_H
#define BALEFIRE_RENDERER_H

#pragma once

#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/Window.h"

namespace BALEFIRE
{
  struct Renderer : RefCounted
  {
    virtual ~Renderer(){}
    virtual void configure() {}
    virtual void configure_window( Window* window ) {}
  };
};

#endif // BALEFIRE_RENDERER_H
