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
    int  width, height;
    int  pixel_width, pixel_height;
    bool rendering_paused = false;

    WindowFrameworkContext* framework_context = nullptr;
    WindowRenderer*    renderer = nullptr;

    Window( Framework* framework, int index, int width, int height ) : framework(framework),
        index(index), width(width), height(height), pixel_width(width), pixel_height(height) {}

    virtual ~Window();

    void render( unsigned char* render_data, int count );
    void update_pixel_size();
  };
};

