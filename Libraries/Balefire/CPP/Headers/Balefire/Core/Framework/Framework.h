#ifndef BALEFIRE_FRAMEWORK_H
#define BALEFIRE_FRAMEWORK_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Balefire;
  struct GraphicsAPI;
  struct Window;

  struct Framework
  {
    Balefire* balefire = nullptr;
    GraphicsAPI* graphics_api = nullptr;

    virtual ~Framework();
    virtual void     configure();
    virtual Window*  create_window( int index, std::string name ) { return nullptr; }
    virtual bool     handle_events() { return false; }
    virtual void     render( Window* window, unsigned char* render_data, int count );
    virtual void     update_pixel_size( Window* window ) {}
  };
};

#endif // BALEFIRE_FRAMEWORK_H
