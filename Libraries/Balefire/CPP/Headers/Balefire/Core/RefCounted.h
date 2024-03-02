#ifndef BALEFIRE_REF_COUNTED_H
#define BALEFIRE_REF_COUNTED_H

#pragma once

#include <cstdio>
#include "Balefire/Core/Types.h"

namespace Balefire
{

struct RefCounted
{
  Int64 refcount = 0;

  ~RefCounted()
  {
    if (refcount)
    {
      fprintf( stderr, "[WARNING] retained, RefCounted object deleted without refcount reaching 0.\n" );
    }
  }

  void release()
  {
    if (!--refcount)
    {
      delete this;
    }
  }

  void retain()
  {
    ++refcount;
  }
};

}; // namespace Balefire

#endif // BALEFIRE_REF_COUNTED_H
