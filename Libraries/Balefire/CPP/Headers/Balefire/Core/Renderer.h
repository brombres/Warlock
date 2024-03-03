#ifndef BALEFIRE_RENDERER_H
#define BALEFIRE_RENDERER_H

#pragma once

#include "Balefire/Core/RefCounted.h"

namespace BALEFIRE
{
  struct Renderer : RefCounted
  {
    virtual ~Renderer(){}
    virtual void configure() {}
  };
};

#endif // BALEFIRE_RENDERER_H
