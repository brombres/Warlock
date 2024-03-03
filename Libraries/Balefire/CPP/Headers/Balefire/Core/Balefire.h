#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/ResourceBank.h"
#include "Balefire/Core/String.h"
#include "Balefire/Core/Window.h"

namespace BALEFIRE
{
  struct Balefire : RefCounted
  {
    ResourceBank<WindowID,Ref<Window>> windows;
    Ref<Renderer> renderer;

    virtual ~Balefire();
    virtual void configure();
    virtual WindowID create_window( String name ) { return (WindowID)0; }
  };
};

#endif // BALEFIRE_H
