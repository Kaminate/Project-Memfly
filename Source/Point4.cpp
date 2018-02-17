/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Point4.cpp
Purpose: Implements the Point struct, which is a float4 representing
  a point in 3d space (the w component defaults to 1)
Language: C++, cl compiler 15.00.21022.08 for 80x86
Platform: Any
Project: nathan.p_CS250_1
Author: Nathan Park, nathan.p, 5005211
Creation date: 1/14/2013
End Header --------------------------------------------------------*/


#include "Point4.h"
#include "Vector4.h"


static const float EPSILON = 0.0001f;

std::istream & operator >> (std::istream & lhs, Point4 & vec)
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

void Point4::Print(void) const
{
  printf("%5.3f, %5.3f, %5.3f, %5.3f\n",x,y,z,w);
}

// Default constructor, sets x,y,z to zero and w to the defined value
Point4::Point4(void) : x(0), y(0), z(0), w(1)
{

} 

  // Copy constructor, copies every component from the other Point4
Point4::Point4(const Point4& rhs):x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w)
{

}
  
  // Non-Default constructor, self-explanatory
Point4::Point4(float xx, float yy, float zz, float ww /*= 1.0f*/)
  :x(xx),y(yy),z(zz),w(ww)
{

}
  
  // Assignment operator, copies every component from the other Point4
Point4& Point4::operator=(const Point4& rhs)
{
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
  w = rhs.w;
  return *this;
}
  
  // Unary negation operator, negates every component and returns a copy
Point4 Point4::operator-(void) const
{
  return Point4(-x,-y,-z,-w);
}
  
  // Binary subtraction operator, Subtract two Point4s and you get a Vector4
Vector4 Point4::operator-(const Point4&  rhs) const{
  return Vector4(
    x-rhs.x,
    y-rhs.y,
    z-rhs.z,
    w-rhs.w);
  } 

  // Basic vector math operations with points, you can add a Vector4 to a Point4, or subtract
  // a Vector4 from a Point4
Point4  Point4::operator+ (const Vector4& rhs) const
{
  return Point4(x+rhs.x,
                y+rhs.y,
                z+rhs.z,
                w+rhs.w);
}

Point4  Point4::operator- (const Vector4& rhs) const
{
  return Point4(x-rhs.x,
                y-rhs.y,
                z-rhs.z,
                w-rhs.w);
}
  
  // Same as previous two operators, just modifies the original instead of returning a copy
Point4& Point4::operator+=(const Vector4& rhs){
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  w+=rhs.w;
  return *this;
}
Point4& Point4::operator-=(const Vector4& rhs){
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  w-=rhs.w;
  return *this;
};


Point4 & Point4::operator/=( const float & rhs )
{
  x /= rhs;
  y /= rhs;
  z /= rhs;
  w /= rhs;
  return *this;
}


  // Comparison operators which should use an epsilon defined in 
  // Utilities.h to see if the value is within a certain range
  // in which case we say they are equivalent.
bool Point4::operator==(const Point4& rhs) const{
  return (   (abs(x-rhs.x) < EPSILON)
          && (abs(y-rhs.y) < EPSILON)
          && (abs(z-rhs.z) < EPSILON)
          && (abs(w-rhs.w) < EPSILON)
          );
}

bool Point4::operator!=(const Point4& rhs) const{
  return (   (abs(x-rhs.x) > EPSILON)
          || (abs(y-rhs.y) > EPSILON)
          || (abs(z-rhs.z) > EPSILON)
          || (abs(w-rhs.w) > EPSILON)
          );
}
  
  // Sets x,y,z to zeroes, w to defined value
void Point4::Zero(void){
  x=y=z=0;
  w=1;
}
