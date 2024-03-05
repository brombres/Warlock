#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include "Balefire/Core/Framework.h"
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

    Ref<Framework> framework;

    Balefire() {}
    Balefire( Framework* framework );

    ~Balefire();
    void     configure( Framework* framework );
    WindowID create_window( String name );
    void     render();
  };
};

#endif // BALEFIRE_H
