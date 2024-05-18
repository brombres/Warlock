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
    virtual void     configure();
    virtual Window*  create_window( int index, std::string name ) { return nullptr; }
    virtual bool     handle_events() { return false; }
    virtual void     render( Window* window, CmdData* data );
    virtual void     update_pixel_size( Window* window ) {}
  };
};

#endif // BALEFIRE_FRAMEWORK_H
