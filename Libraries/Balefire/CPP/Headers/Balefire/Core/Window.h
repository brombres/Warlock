#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Framework;
  struct WindowFrameworkContext;
  struct WindowRenderer;

  struct Window
  {
    Framework* framework;
    int  index = 0;
    int  logical_width, logical_height;
    int  width, height;
    bool rendering_paused = false;

    WindowFrameworkContext* framework_context = nullptr;
    WindowRenderer*    renderer = nullptr;

    Window( Framework* framework, int index, int width, int height ) : framework(framework),
        index(index), logical_width(width), logical_height(height), width(width), height(height) {}

    virtual ~Window();

    void render( unsigned char* render_data, int count );
    void update_pixel_size();
  };
};

