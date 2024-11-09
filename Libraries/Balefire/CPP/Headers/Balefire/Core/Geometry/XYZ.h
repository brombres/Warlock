#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct XYZ : XY
  {
    // PROPERTIES
    Real64 z;

    // CONSTRUCTORS
    XYZ() : XY(), z(0) {}
    XYZ( Real64 x, Real64 y, Real64 z=0 ) : XY(x,y), z(z) {}
    XYZ( XY xy, Real64 z=0 ) : XY(xy), z(z) {}
    XYZ( XYZ& other ) : XY(other.x,other.y), z(other.z) {}

    // METHODS
    operator glm::dvec3() { return glm::dvec3( x, y, z ); }
    operator glm::vec3()  { return glm::vec3( glm::dvec3( x, y, z ) ); }
    operator XY()         { return XY(x,y); }

    XY xy() { return XY(x,y); }
  };
}; // namespace BALEFIRE
