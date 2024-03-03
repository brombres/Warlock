#ifndef BALEFIRE_WINDOW_H
#define BALEFIRE_WINDOW_H

#pragma once

#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/WindowFrameworkContext.h"
#include "Balefire/Core/WindowRendererContext.h"

typedef int WindowID;

namespace BALEFIRE
{
  struct Window : RefCounted
  {
    WindowID id;
    Ref<WindowFrameworkContext> framework_context;
    Ref<WindowRendererContext>  renderer_context;
  };
};

#endif // BALEFIRE_WINDOW_H
