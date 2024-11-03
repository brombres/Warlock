#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct XYZ
  {
    // PROPERTIES
    Real64 x, y, z;

    // CONSTRUCTORS
    XYZ() : x(0), y(0), z(0) {}
    XYZ( Real64 x, Real64 y, Real64 z=0 ) : x(x), y(y), z(z) {}

    // METHODS
    operator glm::dvec3() { return glm::dvec3( x, y, z ); }
    operator glm::vec3()  { return glm::vec3( glm::dvec3( x, y, z ) ); }
  };
}; // namespace BALEFIRE
