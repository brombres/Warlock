#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Matrix
  {
    // GLOBAL METHODS
    static Matrix frustum( Real64 left, Real64 right, Real64 bottom, Real64 top, Real64 z_near, Real64 z_far );
    static Matrix mode_2dx( Real64 width, Real64 height, Real64 depth_scale=1.0,
                            XY perspective_center=XY(0.5,0.5) );
    static Matrix translate( XYZ offset );

    // PROPERTIES
    glm::dmat4 data;

    // CONSTRUCTORS
    Matrix() : data(1.0) {}
    Matrix( glm::dmat4 m ) : data(m) {}
    Matrix( glm::mat4 m ) : data(glm::dmat4(m)) {}

    // METHODS
    glm::dmat4::col_type& operator[]( UInt32 index ) { return data[index]; }

    Matrix operator*( Matrix other ) { return Matrix( (glm::dmat4)(*this) * (glm::dmat4)other ); }

    XYZW operator*( XY xy )
    {
      glm::dvec4 product = (glm::dmat4)(*this) * (glm::dvec4)XYZW(xy);
      return XYZW( product.x, product.y, product.z, product.w );
    }

    XYZW operator*( XYZ xyz )
    {
      glm::dvec4 product = (glm::dmat4)(*this) * (glm::dvec4)XYZW(xyz);
      return XYZW( product.x, product.y, product.z, product.w );
    }

    XYZW operator*( XYZW xyzw )
    {
      glm::dvec4 product = (glm::dmat4)(*this) * (glm::dvec4)xyzw;
      return XYZW( product.x, product.y, product.z, product.w );
    }

    operator glm::dmat4() { return data; }
    operator glm::mat4()  { return glm::mat4(data); }
  };
}; // namespace BALEFIRE
