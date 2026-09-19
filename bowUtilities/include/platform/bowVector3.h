#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK{
class BOW_UTILITIES_EXPORT Vector3{
public:

  /*
  * @brief
  *  Default constructor.
  */
  Vector3() = default;

  /*
  * @brief
  *  Constructor from given values.
  * @param float
  *  Values to make the vector ?
  */
  Vector3(float X, float Y, float Z);

  /*
  * @brief
  *  Constructor from  array
  */
  explicit Vector3(const float values[3]);

  /*
  * @brief
  *  Cosntructor from Vector3.
  */
  //Vector3(const Vector3 vector, float Z);

  /*
  * @brief
  *  Default destructor.
  */
  ~Vector3() = default;

  /*
  * @brief
  *  Calculates the dor product from 2 vectors.
  * @param
  *  Vector3
  * @return float
  *  The dot product from 2 vectors.
  */
  float
  dot(const Vector3& vector) const;
  
  /*
  * @brief
  * Calculates the cross product from 2 given vectors.
  * @param Vector3
  * @return float
  * Returns the cross product from 2 vectors.
  */
  Vector3
  cross(const Vector3& vector) const;

  /*
  * @brief
  *  Calculates the magnitude from this vector.
  * @param NONE
  * @return float
  *  Return the magnitude from this vector.
  */
  float
  magnitude() const;
  
  /*
  * @brief
  * @param NONE
  * @return float
  */
  float
  sqrMagnitude() const;

  /*
  * @brief
  *  Calculates the distance between this and another vector.
  * @para Vector3
  * @return float
  * Returns the distance in float values.
  */
  float
  distance(const Vector3& vector) const;

  /*
  * @brief
  * @param Vector3
  * @return Float
  */
  float
  sqrDistance(const Vector3& vector) const;

  /*
  * @brief
  *  Normalize this vector.
  * @param NONE
  * @return vector3
  *  Returns this vector as a new one but normalized.
  */
  Vector3
  normalize() const;

  /********************************************/
/*  OPERTATORS  */
/********************************************/

/*
* @brief
*  Makes an addition to the values of the vector with a given value.
* @param cons Vector3
* @return Vector3&
*/
  Vector3&
    operator+=(const Vector3& vector) noexcept;


  /*
  * @brief
  *  Substracts the value in the vector for a given value.
  * @param Const Vector3
  * @return Vector3&
  */
  Vector3&
    operator-=(const Vector3& vector) noexcept;

  /*
  * @brief
  *  Multiplies the vector for a given value.
  * @param float
  * @return Vector3&
  */
  Vector3&
    operator*=(float scalar) noexcept;

  /*
  * @brief
  * @param float
  * @return Vector3&
  */
  Vector3&
    operator/=(float scalar) noexcept;

  /*
  * @brief
  *  Makes the addition between a value and the values in the vector.
  * @param Vector3
  * @return Vector3&
  *  Returns the
  */
  Vector3
    operator+(Vector3& value) const noexcept;

  /*
  * @brief
  *  Makes the substraction between a value and the values in the vector.
  * @param Vector3
  * @return Vector3&
  *  Returns a pointer to a substracted vector.
  */
  Vector3
  operator-(Vector3& value) const noexcept;

  /*
  * @brief
  *  Multiplies the values of this for the scalar.
  * @param float Scalar.
  * @return Vector3&
  *  Returns pointer to this as a multiplied vector.
  */
  Vector3
    operator*(float scalar) const noexcept;

  /*
  * @brief
  *  Divides the values in a vector vector
  * @param float
  *  Scalar to divide the vector to.
  * @return Vector3
  */
  Vector3
    operator/(float scalar) const noexcept;

  /*
  * @brief
  *  Checks if all the values in the vectors are the same.
  * @param Vector3
  * @return bool
  *  Returns true if both values are the same.
  */
  bool
    operator==(const Vector3& value) const noexcept;

  /*
  * @brief
  *  Checks if any of the values inside a vector are different to this.
  * @param Vector3&
  * @return true
  *  Returns true if any of the values are different.
  */
  bool
    operator!=(const Vector3& vector) const noexcept;


  float x;
  float y;
  float z;
};

FORCELINE Vector3&
Vector3::operator+=(const Vector3& vector) noexcept {
  x += vector.x;
  y += vector.y;
  z += vector.z;
  return *this;
}

FORCELINE Vector3&
Vector3::operator-=(const Vector3& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  return *this;
}

FORCELINE Vector3&
Vector3::operator*=(float scalar) noexcept {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

FORCELINE Vector3& //return ref, no const
Vector3::operator/=(float scalar) noexcept {
  if (scalar != 0.0f) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }
}

FORCELINE Vector3
Vector3::operator* (float scalar) const noexcept {
  return Vector3(x * scalar, y * scalar, z * scalar);
}

FORCELINE Vector3
Vector3::operator+(Vector3& vector) const noexcept {
  return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

FORCELINE Vector3
Vector3::operator-(Vector3& vector)const noexcept {
  return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

FORCELINE Vector3
Vector3:: operator/(float scalar) const noexcept {
  return Vector3 (x / scalar, y / scalar, z / scalar);
}

FORCELINE bool
Vector3::operator==(const Vector3& vector) const noexcept { //const func
  return x == vector.x && y == vector.y && z == vector.z;
}

FORCELINE bool
Vector3::operator!=(const Vector3& vector) const noexcept {
  return x != vector.x || y != vector.y || z != vector.z;
}

}