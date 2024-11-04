#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct XYZ
  {
    // PROPERTIES
    XY     xy;
    Real64 z;

    // CONSTRUCTORS
    XYZ() : xy(), z(0) {}
    XYZ( Real64 x, Real64 y, Real64 z=0 ) : xy(x,y), z(z) {}

    // METHODS
    operator glm::dvec3() { return glm::dvec3( xy.x, xy.y, z ); }
    operator glm::vec3()  { return glm::vec3( glm::dvec3( xy.x, xy.y, z ) ); }
  };
}; // namespace BALEFIRE
