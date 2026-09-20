#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT Vector2_int
{
public:

  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/
  /*
  * @brief
  *  Default constructor.
  * @parma NONE
  */
  Vector2_int() = default;

  /* @brief
  *  Constructor from given values
  * @param int int
  */
  Vector2_int(int x, int y);

  /*
  * @brief
  *  Constructor from an array.
  * @param int [2]
  */
  explicit Vector2_int(const int values[2]);

  /*
  * @brief
  *  Default destructor.
  */
  ~Vector2_int() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
  *  Calculates the dot product with another vector.
  * @param const Vector2_int&
  * @return
  *  Returns the dot product claculates with another vector.
  */
  int
  dot(const Vector2_int& vector) const;

  /*
  * @brief
  *  Calculates the cross product with another vector.
  * @param const Vector2_int&
  * @return
  *  Cross product from 2 vectors.
  */
  int
  cross(const Vector2_int& vector) const;

  /*
  * @brief
  *  Calculates the magnitude (lenght of the vector).
  * @param NONE
  * @return int
  *  The lenght of the vector.
  */
  float
  magnitude() const;

  /*
  * @brief
  *  Calculates the square magnitude (lengh) of this vector.
  * @param NONE
  * @return
  *  The lenght of the vector.
  */
  int
  sqrMagitude()const;

  /*
  * @brief
  *  Calculates the distance between this and another vector.
  * @param const Vector2_int&
  * @return int
  *  Returns the distance between two vectors.
  */
  int
  distance(const Vector2_int& vector) const;

  /*
  * @brief
  *  Calculates the distance between two vectors without using sqr.
  * @param cosnt Vector2_int
  * @return float
  *  Returns the raw distance between two vectors.
  */
  int
  sqrDistance(const Vector2_int& vector) const;

  /*
  * @brief
  *  Normalize this vecctor
  * @param NONE
  * @return
  *  Returns a new normalize vector2 (This new vectors are float, its values)
  */
  //Vector2
  //  normalize() const;

  /********************************************/
  /*  OPERATORS  */
  /********************************************/
  /*
  * @brief
  *  Makes an addition to the values of the vector with a given value.
  * @param cons vector2
  * @return Vector2&
  */
  Vector2_int&
  operator+=(const Vector2_int& vector) noexcept;


  /*
  * @brief
  *  Substracts the value in the vector for a given value.
  * @param Const Vector2_int
  * @return Vector2_int&
  */
  Vector2_int&
  operator-=(const Vector2_int& vector) noexcept;

  /*
  * @brief
  *  Multiplies the vector for a given value.
  * @param float
  * @return Vector2&
  */
  Vector2_int&
  operator*=(float scalar) noexcept;

  /*
  * @brief
  * @param float
  * @return Vector2&
  */
  Vector2_int&
  operator/=(float scalar) noexcept;

  /*
  * @brief
  *  Makes the addition between a value and the values in the vector.
  * @param Vector2_int
  * @return Vector2_int&
  *  Returns the
  */
  Vector2_int
  operator+(const Vector2_int& value) const noexcept;

  /*
  * @brief
  *  Makes the substraction between a value and the values in the vector.
  * @param Vector2_int
  * @return Vector2_int&
  *  Returns a pointer to a substracted vector.
  */
  Vector2_int
  operator-(const Vector2_int& value) const noexcept;

  /*
  * @brief
  *  Multiplies the values of this for the scalar.
  * @param float Scalar.
  * @return Vector2_int&
  *  Returns pointer to this as a multiplied vector.
  */
  Vector2_int
  operator*(float scalar)const noexcept;

  /*
  * @brief
  *  Divides the values in a vector vector
  * @param float
  *  Scalar to divide the vector to.
  * @return Vector2_int
  */
  Vector2_int
    operator/(float scalar) const noexcept;

  /*
  * @brief
  *  Checks if all the values in the vectors are the same.
  * @param Vector2_int
  * @return bool
  *  Returns true if both values are the same.
  */
  bool
  operator==(const Vector2_int& value) const noexcept;

  /*
  * @brief
  *  Checks if any of the values inside a vector are different to this.
  * @param Vector2_int&
  * @return true
  *  Returns true if any of the values are different.
  */
  bool
  operator!=(const Vector2_int& vector) const noexcept;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  int x;
  int y;

}; // end class Vector2_int

// Method definitions remain inside the namespace
FORCELINE Vector2_int&
Vector2_int::operator+=(const Vector2_int& vector) noexcept {
  x += vector.x;
  y += vector.y;
  return *this;
}

FORCELINE Vector2_int&
Vector2_int::operator-=(const Vector2_int& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
  return *this;
}

FORCELINE Vector2_int&
Vector2_int::operator*=(float scalar) noexcept {
  x *= scalar;
  y *= scalar;
  return *this;
}

FORCELINE Vector2_int&
Vector2_int::operator/=(float scalar) noexcept {
  x /= scalar;
  y /= scalar;
  return *this;
}

FORCELINE Vector2_int
Vector2_int::operator* (float scalar) const noexcept {
  return Vector2_int(x * scalar, y * scalar);
}

FORCELINE Vector2_int
Vector2_int::operator+(const Vector2_int& vector) const noexcept {
  return Vector2_int(x + vector.x, y + vector.y);
}

FORCELINE Vector2_int
Vector2_int::operator-(const Vector2_int& vector) const noexcept {
  return Vector2_int(x - vector.x, y - vector.y);
}

FORCELINE Vector2_int
Vector2_int:: operator/(float scalar) const noexcept {
  return Vector2_int(x / scalar, y / scalar);
}

} 