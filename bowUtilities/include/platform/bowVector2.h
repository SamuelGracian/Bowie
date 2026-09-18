#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT Vector2
{
public:

  /*
  * @brief
     Defautl constructor.
  */
  Vector2() = default;

  /*
  * @brief
     Constructor with given values.
  */
  Vector2(float X, float Y);

  /*
  * @brief
  *  Constructor from array.
  */
  explicit Vector2(const float values[2]);

  /*
  * @brief
     Default destructor.
  */
  ~Vector2() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
     Dot product from two vector 2.
  * @param Vector2
     Vector2 The vector2 to calculate the dot product with.
  * @return float
     float The dot product from this vector2 and the param.
  */
  float
    dot(const Vector2& vector2) const;

  /*
  * @brief
  *  Calculates the cross product from 2 vectors.
  * @Param Vector2
  * @return float
  *  Cross product from 2 vectors.
  */
  float
    cross(const Vector2& vector2) const;

  /*
  * @brief
  *  Calculates the magnitude (lenght of the vector).
  * @param NONE
  * @return float
  *  The lenght of the vector.
  */
  float
    magnitude() const;

  /*
  * @brief
  *  Calculates the square magnitude (lengh) of this vector.
  * @param NONE
  * @return float
  *  The square lenght of this vector.
  */
  float
    sqrMagnitude() const;

  /*
  * @brief
  *  Calculates the diatance between two vectors.
  * @param Vector2
  *  The vector to calculate the distance with.
  * @return float
  *  Returns the distance between two vectors
  */
  float
    distance(const Vector2& vector) const;

  /*
  * @brief
  *  Calculates the square distence betweeen 2 vectors without using sqrt.
  * @param Vector2
  *  The vector to calculate the square distance to.
  * @return float
  *  The square distance between this vector and the one given as param.
  */
  float
    sqrDistance(const Vector2& vector) const;

  /*
  * @brief
  *  Normalize this vector.
  * @return Vector2
  *  This as a normalized vector.
  */
  Vector2
    normalize() const;

  /********************************************/
  /*  OPERTATORS  */
  /********************************************/

  /*
  * @brief
  *  Makes an addition to the values of the vector with a given value.
  * @param cons vector2 
  * @return Vector2&
  */
  Vector2&
    operator+=(const Vector2& vector) noexcept;


  /*
  * @brief
  *  Substracts the value in the vector for a given value.
  * @param Const Vector2
  * @return Vector2&
  */
  Vector2&
    operator-=(const Vector2& vector) noexcept;

  /*
  * @brief
  *  Multiplies the vector for a given value.
  * @param float
  * @return Vector2&
  */
  Vector2&
  operator*=(float scalar) noexcept;
  
  /*
  * @brief
  * @param float
  * @return Vector2&
  */
  Vector2&
  operator/=(float scalar) noexcept;
  
  /*
  * @brief
  *  Makes the addition between a value and the values in the vector.
  * @param Vector2
  * @return Vector2&
  *  Returns the 
  */
  Vector2&
  operator+(Vector2 value) noexcept;

  /*
  * @brief
  *  Makes the substraction between a value and the values in the vector.
  * @param Vector2
  * @return Vector2&
  *  Returns a pointer to a substracted vector.
  */
  Vector2&
  operator-(Vector2 value) noexcept;

  /*
  * @brief
  *  Multiplies the values of this for the scalar.
  * @param float Scalar.
  * @return Vector2&
  *  Returns pointer to this as a multiplied vector.
  */
  Vector2&
  operator*(float scalar) noexcept;

  /*
  * @brief
  *  Divides the values in a vector vector
  * @param float
  *  Scalar to divide the vector to.
  * @return Vector2
  */
  Vector2&
  operator/(float scalar) noexcept;

  /*
  * @brief
  *  Checks if all the values in the vectors are the same.
  * @param Vector2
  * @return bool
  *  Returns true if both values are the same.
  */
  bool
  operator==(const Vector2& value) noexcept;

  /*
  * @brief
  *  Checks if any of the values inside a vector are different to this.
  * @param Vector2&
  * @return true
  *  Returns true if any of the values are different.
  */
  bool
  operator!=(const Vector2& vector) noexcept;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  float x;
  float y;

};

FORCELINE Vector2&
Vector2::operator+=(const Vector2& vector) noexcept {
  x += vector.x;
  y += vector.y;
  return *this;
}

FORCELINE Vector2&
Vector2::operator-=(const Vector2& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
  return *this;
}

FORCELINE Vector2&
Vector2::operator*=(float scalar) noexcept {
  x *= scalar;
  y *= scalar;
  return *this;
}

FORCELINE Vector2&
Vector2::operator/=(float scalar) noexcept {
  x /= scalar;
  y /= scalar;
  return *this;
}

FORCELINE Vector2&
Vector2::operator* (float scalar) noexcept {
  x *= scalar;
  y *= scalar;
  return *this;
}

FORCELINE Vector2&
Vector2::operator+(Vector2 value) noexcept {
  x += value.x;
  y += value.y;
  return *this;
}

FORCELINE Vector2&
Vector2::operator-(Vector2 value) noexcept {
  x -= value.x;
  y -= value.y;
  return *this;
}

FORCELINE Vector2&
Vector2:: operator/(float scalar) noexcept {
  x /= scalar;
  y /= scalar;
  return *this;
}

FORCELINE bool
Vector2::operator==(const Vector2& vector) noexcept {
  if (x == vector.x && y == vector.y) {
    return true;
  }
  else {
    return false;
  }
}


FORCELINE bool
Vector2::operator!=(const Vector2& vector) noexcept {
  if (vector.x != x) {
    return true;
  }
  else if (vector.y != y) {
    return true;
  }
  else {
    return false;
  }
}
}