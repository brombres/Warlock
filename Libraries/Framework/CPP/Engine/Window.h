#ifndef WARLOCK_WINDOW
#define WARLOCK_WINDOW

#pragma once

#include "RefCounted.h"

namespace Warlock
{
  struct WindowData : RefCounted
  {
  };

  typedef SmartPointer<WindowData> Window;
};

#endif // WARLOCK_WINDOW
