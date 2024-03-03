#ifndef BALEFIRE_REF_COUNTED_H
#define BALEFIRE_REF_COUNTED_H

#pragma once

#include <cstdio>
#include "Balefire/Core/Types.h"

namespace BALEFIRE
{

struct RefCounted
{
  Int64 refcount = 0;

  virtual ~RefCounted()
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

}; // namespace BALEFIRE

#endif // BALEFIRE_REF_COUNTED_H
