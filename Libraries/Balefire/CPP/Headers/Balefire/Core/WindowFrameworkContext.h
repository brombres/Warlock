#ifndef BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H
#define BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H

#pragma once

#include "Balefire/Core/RefCounted.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowFrameworkContext : RefCounted
  {
    Window* window;

    WindowFrameworkContext( Window* window ) : window(window) {}
  };
};

#endif // BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H
