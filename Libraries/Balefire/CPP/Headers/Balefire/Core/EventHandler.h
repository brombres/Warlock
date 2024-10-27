#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct EventHandler
  {
    virtual bool begin_render( Window* window, unsigned char** render_data_pointer, int* count_pointer )
    {
      return false;
    }

    virtual void end_render( Window* window ) {}
  };
};
