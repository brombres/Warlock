#ifndef BALEFIRE_FRAMEWORK_H
#define BALEFIRE_FRAMEWORK_H

#pragma once

#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/Renderer.h"
#include "Balefire/Core/ResourceBank.h"
#include "Balefire/Core/String.h"
#include "Balefire/Core/Window.h"

namespace BALEFIRE
{
  struct Balefire;

  struct Framework : RefCounted
  {
    Balefire* balefire = nullptr;
    Ref<Renderer> renderer;

    virtual ~Framework();
    virtual void configure();
    virtual WindowID create_window( String name ) { return (WindowID)0; }
    virtual void     render( Window* window );
  };
};

#endif // BALEFIRE_FRAMEWORK_H
