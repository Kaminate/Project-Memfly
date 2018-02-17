// Nathan Park
// nathan.p
// 50005211
#include "GraphicsMath.h"
#include <math.h> // sin, cos


// returns a matrix that aligns a vector with the z axis
Matrix4 Matrix4AlignZ(const Vector4 & w)
{
  // 1. Rotate w to xy plane
  Vector4 wPrime = Vector4(w.x, 0, w.z);
  float wPrimeMagnitude = wPrime.Length();
  float cosa = w.z / wPrimeMagnitude;
  float sina = w.x / wPrimeMagnitude;
  Matrix4 w_to_xyPlane 
    = Matrix4(cosa, 0, -sina, 0,
                 0, 1,     0, 0,
              sina, 0,  cosa, 0,
                 0, 0,     0, 1);
  // 2. Rotate wxy to z
  float wMagnitude = w.Length();
  float cosb = wPrimeMagnitude / wMagnitude;
  float sinb = w.y / wMagnitude;
  Matrix4 wyz_to_z
    = Matrix4(1,    0,     0, 0,
              0, cosb, -sinb, 0,
              0, sinb,  cosb, 0,
              0,    0,     0, 1);
  return wyz_to_z * w_to_xyPlane;
}

Matrix4 Matrix4Identity()
{
  return Matrix4(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
}

Matrix4 Matrix4Scaling( float sx, float sy, float sz )
{
  return Matrix4(sx, 0, 0, 0,
                  0,sy, 0, 0,
                  0, 0,sz, 0,
                  0, 0, 0, 1);
}

Matrix4 Matrix4RotationXcw( float radians )
{
  float sinr = sin(radians);
  float cosr = cos(radians);

  return Matrix4( 1,     0,     0,  0,
                  0,  cosr, -sinr,  0,
                  0,  sinr,  cosr,  0,
                  0,     0,     0,  1);
}

Matrix4 Matrix4RotationYcw( float radians )
{
  float sinr = sin(radians);
  float cosr = cos(radians);
  
  return Matrix4( cosr,  0, sinr,  0,
                  0,     1,    0,  0,
                 -sinr,  0, cosr,  0,
                  0,     0,     0, 1);
}

Matrix4 Matrix4RotationZcw( float radians )
{
  float sinr = sin(radians);
  float cosr = cos(radians);

  return Matrix4(cosr, -sinr,  0, 0,
                 sinr,  cosr,  0, 0,
                    0,      0, 1, 0,
                    0,      0, 0, 1);
}

Matrix4 Matrix4Trans( float tx, float ty, float tz )
{
  return Matrix4( 1, 0, 0, tx,
                  0, 1, 0, ty,
                  0, 0, 1, tz,
                  0, 0, 0,  1);
}

Matrix4 Matrix4Trans( const Point4 & point )
{
  return Matrix4( 1, 0, 0, point.x,
                  0, 1, 0, point.y,
                  0, 0, 1, point.z,
                  0, 0, 0,       1);
}
