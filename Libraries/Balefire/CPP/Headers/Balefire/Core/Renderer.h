#ifndef BALEFIRE_RENDERER_H
#define BALEFIRE_RENDERER_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct Renderer
  {
    virtual ~Renderer(){}
    virtual void configure() {}
    virtual void configure_window( Window* window ) {}
  };
};

#endif // BALEFIRE_RENDERER_H
