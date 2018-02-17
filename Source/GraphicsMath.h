// Nathan Park
// nathan.p
// 50005211

#ifndef GRAPHICS_MATH_H
#define GRAPHICS_MATH_H

#include "Matrix4.h"
#include "Point4.h"
#include "Vector4.h"

// Assumed: Right-handed coordinates

Matrix4 Matrix4Identity();
Matrix4 Matrix4Scaling(float sx, float sy, float sz);
Matrix4 Matrix4RotationXcw(float radians);
Matrix4 Matrix4RotationYcw(float radians);
Matrix4 Matrix4RotationZcw(float radians);
Matrix4 Matrix4Trans(float tx, float ty, float tz);
Matrix4 Matrix4Trans(const Point4 & point);
Matrix4 Matrix4AlignZ(const Vector4 & w);


// Matrix4 Matrix4InverseScaling(const Matrix4 & scaleMatrix);
// etc etc etc

#endif
