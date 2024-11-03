#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Matrix Matrix::frustum( Real64 left, Real64 right, Real64 bottom, Real64 top, Real64 z_near, Real64 z_far )
{
  return Matrix( glm::frustum(left, right, bottom, top, z_near, z_far) );
}

Matrix Matrix::translate( XYZ offset )
{
  return Matrix( glm::translate( glm::dmat4(1.0f), (glm::dvec3)offset ) );
}
