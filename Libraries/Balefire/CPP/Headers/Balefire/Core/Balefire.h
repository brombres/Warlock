#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/ResourceBank.h"
#include "Balefire/Core/Window.h"

namespace Balefire
{
  struct Balefire : RefCounted
  {
    ResourceBank<WindowID,Window*> windows;

    //virtual WindowID create_window( const
  };
};

#endif // BALEFIRE_H
