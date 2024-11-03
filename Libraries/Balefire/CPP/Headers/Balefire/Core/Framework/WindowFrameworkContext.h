#ifndef BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H
#define BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowFrameworkContext
  {
    Window* window = nullptr;

    WindowFrameworkContext( Window* window ) : window(window) {}
    virtual ~WindowFrameworkContext() {}
  };
};

#endif // BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_H
