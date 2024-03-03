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
  struct Framework : RefCounted
  {
    Ref<Renderer> renderer;

    virtual ~Framework();
    virtual void configure();
    virtual WindowID create_window( String name ) { return (WindowID)0; }
  };
};

#endif // BALEFIRE_FRAMEWORK_H
