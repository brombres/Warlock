#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct XY
  {
    // PROPERTIES
    Real64 x, y;

    // CONSTRUCTORS
    XY() : x(0), y(0) {}
    XY( Real64 value ) : x(value), y(value) {}
    XY( Real64 x, Real64 y ) : x(x), y(y) {}

    // METHODS
    operator glm::dvec2() { return glm::dvec2( x, y ); }
    operator glm::vec2()  { return glm::vec2( glm::dvec2( x, y ) ); }
  };
}; // namespace BALEFIRE
