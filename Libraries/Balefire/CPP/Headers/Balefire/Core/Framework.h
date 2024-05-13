#ifndef BALEFIRE_FRAMEWORK_H
#define BALEFIRE_FRAMEWORK_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Balefire;
  struct Renderer;
  struct Window;

  struct Framework
  {
    Balefire* balefire = nullptr;
    Renderer* renderer = nullptr;

    virtual ~Framework();
    virtual void configure();
    virtual WindowID create_window( std::string name ) { return (WindowID)0; }
    virtual void     render( Window* window );
    virtual void     update_pixel_size( Window* window ) {}
  };
};

#endif // BALEFIRE_FRAMEWORK_H
