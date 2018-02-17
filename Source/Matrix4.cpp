/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix4.cpp
Purpose: Implements the Matrix struct, which has functionalities
 including interacting with points and vectors
Language: C++, cl compiler 15.00.21022.08 for 80x86
Platform: Any
Project: nathan.p_CS250_1
Author: Nathan Park, nathan.p, 5005211
Creation date: 1/14/2013
End Header --------------------------------------------------------*/

#include "Matrix4.h"
#include "Vector4.h"
#include "Point4.h"


static const float EPSILON = 0.0001f;

    // Default constructor should initialize to zeroes
  Matrix4::Matrix4(void)
    : m00(0)
    , m01(0)
    , m02(0)
    , m03(0)

    , m10(0)
    , m11(0)
    , m12(0)
    , m13(0)

    , m20(0)
    , m21(0)
    , m22(0)
    , m23(0)

    , m30(0)
    , m31(0)
    , m32(0)
    , m33(0)
  {
  }

    // Copy constructor, copies every entry from the other matrix.
  Matrix4::Matrix4(const Matrix4& rhs)
    : m00(rhs.m00)
    , m01(rhs.m01)
    , m02(rhs.m02)
    , m03(rhs.m03)

    , m10(rhs.m10)
    , m11(rhs.m11)
    , m12(rhs.m12)
    , m13(rhs.m13)

    , m20(rhs.m20)
    , m21(rhs.m21)
    , m22(rhs.m22)
    , m23(rhs.m23)

    , m30(rhs.m30)
    , m31(rhs.m31)
    , m32(rhs.m32)
    , m33(rhs.m33)
  {
  }
  
    // Non-default constructor, self-explanatory
  Matrix4::Matrix4(
          float mm00, float mm01, float mm02, float mm03,
          float mm10, float mm11, float mm12, float mm13,
          float mm20, float mm21, float mm22, float mm23,
          float mm30, float mm31, float mm32, float mm33)
    : m00(mm00)
    , m01(mm01)      
    , m02(mm02)      
    , m03(mm03)      

    , m10(mm10)      
    , m11(mm11)      
    , m12(mm12)      
    , m13(mm13)      

    , m20(mm20)      
    , m21(mm21)      
    , m22(mm22)      
    , m23(mm23)      

    , m30(mm30)      
    , m31(mm31)      
    , m32(mm32)      
    , m33(mm33)      
  {
  }
  
    // Assignment operator, does not need to handle self-assignment
  Matrix4& Matrix4::operator=(const Matrix4& rhs)
  {
    m00=rhs.m00;
    m01=rhs.m01;
    m02=rhs.m02;
    m03=rhs.m03;
       
    m10=rhs.m10;
    m11=rhs.m11;
    m12=rhs.m12;
    m13=rhs.m13;
       
    m20=rhs.m20;
    m21=rhs.m21;
    m22=rhs.m22;
    m23=rhs.m23;
       
    m30=rhs.m30;
    m31=rhs.m31;
    m32=rhs.m32;
    m33=rhs.m33;
    return *this;
  }
  
    // Multiplying a Matrix4 with a Vector4 or a Point4
  Vector4 Matrix4::operator*(const Vector4& rhs) const
  {
    return Vector4(
      m00*rhs.x + m01*rhs.y + m02*rhs.z + m03*rhs.w,
      m10*rhs.x + m11*rhs.y + m12*rhs.z + m13*rhs.w,
      m20*rhs.x + m21*rhs.y + m22*rhs.z + m23*rhs.w,
      m30*rhs.x + m31*rhs.y + m32*rhs.z + m33*rhs.w
    );
  }
  Point4  Matrix4::operator*(const Point4& rhs) const
  {
    return Point4(
      m00*rhs.x + m01*rhs.y + m02*rhs.z + m03*rhs.w,
      m10*rhs.x + m11*rhs.y + m12*rhs.z + m13*rhs.w,
      m20*rhs.x + m21*rhs.y + m22*rhs.z + m23*rhs.w,
      m30*rhs.x + m31*rhs.y + m32*rhs.z + m33*rhs.w
    );
  }
  
    // Basic Matrix arithmetic operations
  Matrix4 Matrix4::operator+(const Matrix4& rhs) const
  {
    return Matrix4(
      m00+rhs.m00,
      m01+rhs.m01,
      m02+rhs.m02,
      m03+rhs.m03,

      m10+rhs.m10,
      m11+rhs.m11,
      m12+rhs.m12,
      m13+rhs.m13,

      m20+rhs.m20,
      m21+rhs.m21,
      m22+rhs.m22,
      m23+rhs.m23,

      m30+rhs.m30,
      m31+rhs.m31,
      m32+rhs.m32,
      m33+rhs.m33
    );
  }
  Matrix4 Matrix4::operator-(const Matrix4& rhs) const
  {
    return Matrix4(
      m00-rhs.m00,
      m01-rhs.m01,
      m02-rhs.m02,
      m03-rhs.m03,

      m10-rhs.m10,
      m11-rhs.m11,
      m12-rhs.m12,
      m13-rhs.m13,

      m20-rhs.m20,
      m21-rhs.m21,
      m22-rhs.m22,
      m23-rhs.m23,

      m30-rhs.m30,
      m31-rhs.m31,
      m32-rhs.m32,
      m33-rhs.m33
    );
  }

  Matrix4 Matrix4::operator*(const Matrix4& rhs) const
  {
    Matrix4 ret; // zero matrix

    for (unsigned row = 0; row < 4; ++row)
    {
      for (unsigned col = 0; col < 4; ++col)
      {
        for (unsigned i = 0; i < 4; ++i)
        {
          ret.m[row][col] += m[row][i] * rhs.m[i][col];
        }
      }
    }
    return ret;
  }
  
    // Similar to the three above except they modify
    // the original 
  Matrix4& Matrix4::operator+=(const Matrix4& rhs)
  {
    m00+=rhs.m00;
    m01+=rhs.m01;
    m02+=rhs.m02;
    m03+=rhs.m03;
    m10+=rhs.m10;
    m11+=rhs.m11;
    m12+=rhs.m12;
    m13+=rhs.m13;
    m20+=rhs.m20;
    m21+=rhs.m21;
    m22+=rhs.m22;
    m23+=rhs.m23;
    m30+=rhs.m30;
    m31+=rhs.m31;
    m32+=rhs.m32;
    m33+=rhs.m33;
    return *this;
  }
  Matrix4& Matrix4::operator-=(const Matrix4& rhs)
  {
    m00-=rhs.m00;
    m01-=rhs.m01;
    m02-=rhs.m02;
    m03-=rhs.m03;
    m10-=rhs.m10;
    m11-=rhs.m11;
    m12-=rhs.m12;
    m13-=rhs.m13;
    m20-=rhs.m20;
    m21-=rhs.m21;
    m22-=rhs.m22;
    m23-=rhs.m23;
    m30-=rhs.m30;
    m31-=rhs.m31;
    m32-=rhs.m32;
    m33-=rhs.m33;
    return *this;
  }
  Matrix4& Matrix4::operator*=(const Matrix4& rhs)
  {
    Matrix4 temp(*this); 

    return *this = temp * rhs;

  }
  
    // Scale/Divide the entire matrix by a float
  Matrix4 Matrix4::operator*(const float rhs) const
  {
    return Matrix4(
      m00*rhs,
      m01*rhs,
      m02*rhs,
      m03*rhs,
      m10*rhs,
      m11*rhs,
      m12*rhs,
      m13*rhs,
      m20*rhs,
      m21*rhs,
      m22*rhs,
      m23*rhs,
      m30*rhs,
      m31*rhs,
      m32*rhs,
      m33*rhs
    );
  }
  Matrix4 Matrix4::operator/(const float rhs) const
  {
    // if rhs == 0 fuck them
    return Matrix4(
      m00/rhs,
      m01/rhs,
      m02/rhs,
      m03/rhs,
      m10/rhs,
      m11/rhs,
      m12/rhs,
      m13/rhs,
      m20/rhs,
      m21/rhs,
      m22/rhs,
      m23/rhs,
      m30/rhs,
      m31/rhs,
      m32/rhs,
      m33/rhs
    );
  }
  
    // Same as previous 
  Matrix4& Matrix4::operator*=(const float rhs)
  {
    m00*=rhs;
    m01*=rhs;
    m02*=rhs;
    m03*=rhs;
    m10*=rhs;
    m11*=rhs;
    m12*=rhs;
    m13*=rhs;
    m20*=rhs;
    m21*=rhs;
    m22*=rhs;
    m23*=rhs;
    m30*=rhs;
    m31*=rhs;
    m32*=rhs;
    m33*=rhs;
    return *this;
  }
  Matrix4& Matrix4::operator/=(const float rhs)
  {
    m00/=rhs;
    m01/=rhs;
    m02/=rhs;
    m03/=rhs;
    m10/=rhs;
    m11/=rhs;
    m12/=rhs;
    m13/=rhs;
    m20/=rhs;
    m21/=rhs;
    m22/=rhs;
    m23/=rhs;
    m30/=rhs;
    m31/=rhs;
    m32/=rhs;
    m33/=rhs;
    return *this;
  }
  
    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
  bool Matrix4::operator==(const Matrix4& rhs) const
  {
    return(
        (abs(m00 - rhs.m00) < EPSILON)
      &&(abs(m01 - rhs.m01) < EPSILON)
      &&(abs(m02 - rhs.m02) < EPSILON)
      &&(abs(m03 - rhs.m03) < EPSILON)
      &&(abs(m10 - rhs.m10) < EPSILON)
      &&(abs(m11 - rhs.m11) < EPSILON)
      &&(abs(m12 - rhs.m12) < EPSILON)
      &&(abs(m13 - rhs.m13) < EPSILON)
      &&(abs(m20 - rhs.m20) < EPSILON)
      &&(abs(m21 - rhs.m21) < EPSILON)
      &&(abs(m22 - rhs.m22) < EPSILON)
      &&(abs(m23 - rhs.m23) < EPSILON)
      &&(abs(m30 - rhs.m30) < EPSILON)
      &&(abs(m31 - rhs.m31) < EPSILON)
      &&(abs(m32 - rhs.m32) < EPSILON)
      &&(abs(m33 - rhs.m33) < EPSILON)
    ); 
  }
  
  bool Matrix4::operator!=(const Matrix4& rhs) const
  {
    return(
        (abs(m00 - rhs.m00) > EPSILON)
      ||(abs(m01 - rhs.m01) > EPSILON)
      ||(abs(m02 - rhs.m02) > EPSILON)
      ||(abs(m03 - rhs.m03) > EPSILON)
      ||(abs(m10 - rhs.m10) > EPSILON)
      ||(abs(m11 - rhs.m11) > EPSILON)
      ||(abs(m12 - rhs.m12) > EPSILON)
      ||(abs(m13 - rhs.m13) > EPSILON)
      ||(abs(m20 - rhs.m20) > EPSILON)
      ||(abs(m21 - rhs.m21) > EPSILON)
      ||(abs(m22 - rhs.m22) > EPSILON)
      ||(abs(m23 - rhs.m23) > EPSILON)
      ||(abs(m30 - rhs.m30) > EPSILON)
      ||(abs(m31 - rhs.m31) > EPSILON)
      ||(abs(m32 - rhs.m32) > EPSILON)
      ||(abs(m33 - rhs.m33) > EPSILON)
    );
    
  }
  
    // Zeroes out the entire matrix
  void Matrix4::Zero(void)
  {
    m00 = 0;
    m01 = 0;
    m02 = 0;
    m03 = 0;
    m10 = 0;
    m11 = 0;
    m12 = 0;
    m13 = 0;
    m20 = 0;
    m21 = 0;
    m22 = 0;
    m23 = 0;
    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 0;
  }
  
    // Builds the identity matrix
  void Matrix4::Identity(void)
  {
    m00 = 1;
    m01 = 0;
    m02 = 0;
    m03 = 0;
    m10 = 0;
    m11 = 1;
    m12 = 0;
    m13 = 0;
    m20 = 0;
    m21 = 0;
    m22 = 1;
    m23 = 0;
    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 1;
  }


void Matrix4::Print(void) const
{
  printf("--------------------------\n");
  printf("%5.3f %5.3f %5.3f %5.3f\n", m00, m01, m02, m03 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m10, m11, m12, m13 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m20, m21, m22, m23 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m30, m31, m32, m33 );
  printf("--------------------------\n");
}
