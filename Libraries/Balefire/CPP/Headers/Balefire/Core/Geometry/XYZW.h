#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct XYZW : XYZ
  {
    // PROPERTIES
    Real64 w;

    // CONSTRUCTORS
    XYZW() : XYZ(), w(0) {}
    XYZW( Real64 x, Real64 y, Real64 z=0, Real64 w=1 ) : XYZ(x,y,z), w(w) {}
    XYZW( XY xy, Real64 z=0, Real64 w=1 ) : XYZ(xy,z), w(w) {}
    XYZW( XYZ xyz, Real64 w=1 ) : XYZ(xyz), w(w) {}
    XYZW( XYZW& other ) : XYZ( other.x, other.y, other.z ), w(w) {}

    // METHODS
    operator glm::dvec4() { return glm::dvec4(x, y, z, w); }
    operator glm::vec4()  { return glm::vec4( glm::dvec4(x, y, z, w) ); }
    operator XY()         { return XY(x,y); }
    operator XYZ()        { return XYZ(x,y,z); }

    XY  xy()  { return XY(x,y); }
    XYZ xyz() { return XYZ(x,y,z); }
  };
}; // namespace BALEFIRE
