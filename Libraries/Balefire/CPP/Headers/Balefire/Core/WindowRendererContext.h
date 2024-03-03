#ifndef BALEFIRE_WINDOW_RENDERER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDERER_CONTEXT_H

#pragma once

#include "Balefire/Core/RefCounted.h"

namespace BALEFIRE
{
  struct WindowRendererContext : RefCounted
  {
    bool initialized = false;
  };
};

#endif // BALEFIRE_WINDOW_RENDERER_CONTEXT_H
