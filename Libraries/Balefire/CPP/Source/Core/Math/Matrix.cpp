#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Matrix Matrix::frustum( Real64 left, Real64 right, Real64 bottom, Real64 top, Real64 z_near, Real64 z_far )
{
  return Matrix( glm::frustum(left, right, bottom, top, z_near, z_far) );
}

Matrix Matrix::mode_2dx( Real64 width, Real64 height, Real64 depth_scale, XY perspective_center )
{
  Real64 nominal_z = sqrt(width*width + height*height) * depth_scale;
  Real64 max_z = -nominal_z * 2;
  Real64 k = (nominal_z + 1) * 2;
  Real64 left = ((-2 * width) / k)  * perspective_center.x;
  Real64 top  = ((-2 * height) / k) * perspective_center.y;
  Real64 right = left + 2*width/k;
  Real64 bottom = top + 2*height/k;

  return
    Matrix::frustum( left, right, top, bottom, -1, (max_z*k)/3 )
    * Matrix::translate( XYZ(-width*perspective_center.x,-height*perspective_center.y,nominal_z) );
}

Matrix Matrix::translate( XYZ offset )
{
  return Matrix( glm::translate( glm::dmat4(1.0f), (glm::dvec3)offset ) );
}
