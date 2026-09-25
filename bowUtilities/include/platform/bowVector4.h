#pragma once

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT Vector4
{
public:
  /********************************************/
  /*  constructors  */
  /********************************************/
  
  /*
  * @Brief
  * Default connstructor.
  */
  Vector4() = default;

  /*
  * @brief
  *  Constructor from given values.
  */
  Vector4(float X, float Y, float Z, float W);
  
  /*
  * @brief
  *  Constructor from an arrray.
  */
  explicit Vector4(const float values[4]);

  /*
  * @brief
  *  Default destrctor.
  */
  ~Vector4() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * brief
  *  Calculathes the dot product between two vectors.
  * @param CONST VECTOR4
  * @return FLOAT
  *  The scalar result from the dot product.
  */
  float
  dot(const Vector4& vector) const;

  /*
  * @brief 
  *  Calculates the cross product beteen two vectors.
  * @param CONST VECTOR4
  * @return VECTOR4 
  *  A Vector4 containing the 3D cross product with w set to zero.
  */
  Vector4
  cross(const Vector4& vector) const;

  /*
  * @brief
  *  Calculates the magnitude of the vector.
  * @param NONE
  * @return 
  *  The amgnitude of the vector.
  */
  float
  magnitude() const;

  /*
  * @brief
  *  Calculates the square magniude of the vector.
  * @param NONE
  * @return
  *  REturns the square mgnitude of the vector.
  */
  float
  sqrMagnitude() const;

  /*
  * @brief
  *  Calculates the distance between two vectors.
  * @param CONST VECTOR4
  * @return
  *  The distance between two vectors
  */
  float
  distance(const Vector4& vector) const;

  /*
  * @brief
  *  Calculates the square distance betweeen two vectors.
  * @param CONST VECTOR4
  * @return
  *  The distance between two vectors.
  */
  float
  sqrDistance(const Vector4& vector) const;

  Vector4
  normalize() const;

  /********************************************/
  /*  OPERATORS  */
  /********************************************/


  /*
  * @brief
  *  Makes an addition to the values of the vector with a given value.
  * @param cons Vector4
  * @return Vector4&
  */
  FORCELINE Vector4&
  operator+=(const Vector4& vector) noexcept;


  /*
  * @brief
  *  Substracts the value in the vector for a given value.
  * @param Const Vector4
  * @return Vector4&
  */
  FORCELINE Vector4&
  operator-=(const Vector4& vector) noexcept;

  /*
  * @brief
  *  Multiplies the vector for a given value.
  * @param float
  * @return Vector4&
  */
  FORCELINE Vector4&
  operator*=(float scalar) noexcept;

  /*
  * @brief
  * @param float
  * @return Vector4&
  */
  FORCELINE Vector4&
  operator/=(float scalar) noexcept;

  /*
  * @brief
  *  Makes the addition between a value and the values in the vector.
  * @param Vector4
  * @return Vector4&
  *  Returns the
  */
  FORCELINE Vector4
  operator+(const Vector4& value) const noexcept;

  /*
  * @brief
  *  Makes the substraction between a value and the values in the vector.
  * @param Vector4
  * @return Vector4&
  *  Returns a pointer to a substracted vector.
  */
  FORCELINE Vector4
  operator-(const Vector4& value) const noexcept;

  /*
  * @brief
  *  Multiplies the values of this for the scalar.
  * @param float Scalar.
  * @return Vector4&
  *  Returns pointer to this as a multiplied vector.
  */
  FORCELINE Vector4
  operator*(float scalar) const noexcept;

  /*
  * @brief
  *  Divides the values in a vector vector
  * @param float
  *  Scalar to divide the vector to.
  * @return Vector4
  */
  FORCELINE Vector4
  operator/(float scalar) const noexcept;

  /*
  * @brief
  *  Checks if all the values in the vectors are the same.
  * @param Vector4
  * @return bool
  *  Returns true if both values are the same.
  */
  FORCELINE bool
  operator==(const Vector4& value) const noexcept;

  /*
  * @brief
  *  Checks if any of the values inside a vector are different to this.
  * @param Vector4&
  * @return true
  *  Returns true if any of the values are different.
  */
  FORCELINE bool
  operator!=(const Vector4& vector) const noexcept;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  float x;
  float y;
  float z;
  float w;
};


FORCELINE Vector4&
Vector4::operator+=(const Vector4& vector) noexcept {
  x += vector.x;
  y += vector.y;
  z += vector.z;
  w += vector.w;
  return *this;
}

FORCELINE Vector4&
Vector4::operator-=(const Vector4& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  w -= vector.w;
  return *this;
}

FORCELINE Vector4&
Vector4::operator*=(float scalar) noexcept {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

FORCELINE Vector4&
Vector4::operator/=(float scalar) noexcept {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

FORCELINE Vector4
Vector4::operator*(float scalar) const noexcept {
  return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

FORCELINE Vector4
Vector4::operator+(const Vector4& vector) const noexcept {
  return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

FORCELINE Vector4
Vector4::operator-(const Vector4& vector) const noexcept {
  return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

FORCELINE Vector4
Vector4:: operator/(float scalar) const noexcept {
  return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

FORCELINE bool
Vector4::operator==(const Vector4& vector) const noexcept {
  return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}


FORCELINE bool
Vector4::operator!=(const Vector4& vector) const noexcept {
  return x != vector.x || y != vector.y;
}
}