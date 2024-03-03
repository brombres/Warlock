#ifndef BALEFIRE_WINDOW_H
#define BALEFIRE_WINDOW_H

#pragma once

#include "Balefire/Core/RefCounted.h"

typedef int WindowID;

namespace BALEFIRE
{
  struct Window : RefCounted
  {
    WindowID id;
  };
};

#endif // BALEFIRE_WINDOW_H
