/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector4.cpp
Purpose: Implements the Vector struct, which is a float4 representing
  a vector in 3d space (the w component defaults to 0)
Language: C++, cl compiler 15.00.21022.08 for 80x86
Platform: Any
Project: nathan.p_CS250_1
Author: Nathan Park, nathan.p, 5005211
Creation date: 1/14/2013
End Header --------------------------------------------------------*/

#include "Vector4.h"

#include <string>

static const float EPSILON = 0.0001f;

std::istream & operator >> (std::istream & lhs, Vector4 & vec)
{
    char comma;
    //std::string comma;
    lhs >> vec.x;
    lhs >> comma;
    lhs >> vec.y;
    lhs >> comma;
    lhs >> vec.z;
    lhs >> comma;
    lhs >> vec.w;
    return lhs;
}

  // Default constructor, initializes x,y,z to zeroes, w to defined value
  Vector4::Vector4(void) : x(0),y(0),z(0),w(0){
  }
  
    // Copy constructor, copies every component from the other Vector4
  Vector4::Vector4(const Vector4& rhs)
    : x(rhs.x)
    , y(rhs.y)
    , z(rhs.z)
    , w(rhs.w)
  {
  }

  
    // Non-Default constructor, self explanatory
  Vector4::Vector4(float xx, float yy, float zz, float ww /* = 0 */)
    : x(xx)
    , y(yy)
    , z(zz)
    , w(ww)
  {
  }
  
    // Assignment operator, does not need to handle self assignment
  Vector4& Vector4::operator=(const Vector4& rhs){
    x=rhs.x;y=rhs.y;z=rhs.z;w=rhs.w;
    return *this;
  }
  
    // Unary negation operator, negates all components and returns a copy
  Vector4 Vector4::operator-(void) const {
    return Vector4(-x,-y,-z,-w);
  }
    
    // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
    // from Vector B, or multiply a vector with a scalar, or divide a vector by 
    // that scalar
  Vector4  Vector4::operator+(const Vector4& rhs) const{
    return Vector4(x+rhs.x,
                   y+rhs.y,
                   z+rhs.z,
                   w+rhs.w);
  }
  Vector4 Vector4::operator-(const Vector4& rhs) const{
    return Vector4(x-rhs.x,
                   y-rhs.y,
                   z-rhs.z,
                   w-rhs.w);
  }
  Vector4 Vector4::operator*(const float rhs) const{
  return Vector4(x*rhs,
                 y*rhs,
                 z*rhs,
                 w*rhs);
  }
  Vector4 Vector4::operator/(const float rhs) const{
  // If rhs == 0, fuck them
  return Vector4(x/rhs,
                 y/rhs,
                 z/rhs,
                 w/rhs);
  }
  
    // Same as above, just stores the result in the original vector
  Vector4& Vector4::operator+=(const Vector4& rhs){
    x+=rhs.x; 
    y+=rhs.y; 
    z+=rhs.z; 
    w+=rhs.w;
    return *this;
  }
  Vector4& Vector4::operator-=(const Vector4& rhs){
    x-=rhs.x; 
    y-=rhs.y; 
    z-=rhs.z; 
    w-=rhs.w;
    return *this;
  }
  Vector4& Vector4::operator*=(const float rhs){
    x*=rhs; 
    y*=rhs; 
    z*=rhs; 
    w*=rhs;
    return *this;
  }
  Vector4& Vector4::operator/=(const float rhs){
    x/=rhs; 
    y/=rhs; 
    z/=rhs; 
    w/=rhs;
    return *this;
   }
  
    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
  bool Vector4::operator==(const Vector4& rhs) const
  {
    return abs(x-rhs.x) < EPSILON
        && abs(y-rhs.y) < EPSILON
        && abs(z-rhs.z) < EPSILON
        && abs(w-rhs.w) < EPSILON; 
  }
  bool Vector4::operator!=(const Vector4& rhs) const
  {
    return abs(x-rhs.x) > EPSILON
        || abs(y-rhs.y) > EPSILON
        || abs(z-rhs.z) > EPSILON
        || abs(w-rhs.w) > EPSILON;
  }
  
    // Computes the dot product with the other vector. Treat it as 3D vector.
  float Vector4::Dot(const Vector4& rhs) const{
    return x * rhs.x 
         + y * rhs.y
         + z * rhs.z
         ; // + w * rhs.w; NOPE
  }
  
    // Computes the cross product with the other vector. Treat it as a 3D vector.
  Vector4 Vector4::Cross(const Vector4& rhs) const{
    // i j k   i = +(yc-zb)
    // x y z   j = -(xc-za) = za-xc
    // a b c   k = +(xb-ya)
    return Vector4(y*rhs.z - z*rhs.y,
                   z*rhs.x - x*rhs.z,
                   x*rhs.y - y*rhs.x,
                   0);
  }
  
    // Computes the true length of the vector 
  float Vector4::Length(void) const{
    return sqrt(x*x+y*y+z*z+w*w);
  }
  
    // Computes the squared length of the vector
  float Vector4::LengthSq(void) const{
    return x*x + y*y + z*z + w*w;
  }
  
    // Normalizes the vector to make the final vector be of length 1. If the length is zero
    // then this function should not modify anything.
  void Vector4::Normalize(void){
    float length = Length();
    if (length) (*this)/=length;
  }
  
    // Sets x,y,z to zeroes, w to defined value
  void Vector4::Zero(void){
    x=y=z=w=0;
  }

void Vector4::Print(void) const
{
  printf("%5.3f, %5.3f, %5.3f, %5.3f\n",x,y,z,w);
}
