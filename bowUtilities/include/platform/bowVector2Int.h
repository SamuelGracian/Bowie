#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT Vector2Int
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
  Vector2Int() = default;

  /* @brief
  *  Constructor from given values
  * @param int int
  */
  Vector2Int(int32 x, int32 y);

  /*
  * @brief
  *  Constructor from an array.
  * @param int [2]
  */
  explicit Vector2Int(const int32 values[2]);

  /*
  * @brief
  *  Default destructor.
  */
  ~Vector2Int() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
  *  Calculates the dot product with another vector.
  * @param const Vector2Int&
  * @return
  *  Returns the dot product claculates with another vector.
  */
  int32
  dot(const Vector2Int& vector) const;

  /*
  * @brief
  *  Calculates the cross product with another vector.
  * @param const Vector2Int&
  * @return
  *  Cross product from 2 vectors.
  */
  int32
  cross(const Vector2Int& vector) const;

  /*
  * @brief
  *  Calculates the magnitude (lenght of the vector).
  * @param NONE
  * @return int
  *  The lenght of the vector.
  */
  //float
  //magnitude() const;

  /*
  * @brief
  *  Calculates the square magnitude (lengh) of this vector.
  * @param NONE
  * @return
  *  The lenght of the vector.
  */
  int32
  sqrMagitude() const;

  /*
  * @brief
  *  Calculates the distance between this and another vector.
  * @param const Vector2Int&
  * @return int
  *  Returns the distance between two vectors.
  */
  //int
  //distance(const Vector2Int& vector) const;

  /*
  * @brief
  *  Calculates the distance between two vectors without using sqr.
  * @param cosnt Vector2Int
  * @return INT
  *  Returns the raw distance between two vectors.
  */
  int32
  sqrDistance(const Vector2Int& vector) const;

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
  /*  MEMBERS  */

  /********************************************/
  
  int x;
  int y;

  /********************************************/
  /*  OPERATORS  */
  /********************************************/
  /*
  * @brief
  *  Makes an addition to the values of the vector with a given value.
  * @param cons vector2
  * @return Vector2&
  */
  FORCELINE Vector2Int&
  operator+=(const Vector2Int& vector) noexcept;


  /*
  * @brief
  *  Substracts the value in the vector for a given value.
  * @param Const Vector2Int
  * @return Vector2Int&
  */
  FORCELINE Vector2Int&
  operator-=(const Vector2Int& vector) noexcept;

  /*
  * @brief
  *  Multiplies the vector for a given value.
  * @param INT 
  * @return Vector2&
  */
  FORCELINE Vector2Int&
  operator*=(int scalar) noexcept;

  /*
  * @brief
  * @param INT
  * @return Vector2&
  */
  FORCELINE Vector2Int&
  operator/=(int scalar) noexcept;

  /*
  * @brief
  *  Makes the addition between a value and the values in the vector.
  * @param Vector2Int
  * @return Vector2Int&
  *  Returns the
  */
  FORCELINE Vector2Int
  operator+(const Vector2Int& value) const noexcept;

  /*
  * @brief
  *  Makes the substraction between a value and the values in the vector.
  * @param Vector2Int
  * @return Vector2Int&
  *  Returns a pointer to a substracted vector.
  */
  FORCELINE Vector2Int
  operator-(const Vector2Int& value) const noexcept;

  /*
  * @brief
  *  Multiplies the values of this for the scalar.
  * @param INT
  * @return Vector2Int&
  *  Returns pointer to this as a multiplied vector.
  */
  FORCELINE Vector2Int
  operator*(int scalar) const noexcept;

  /*
  * @brief
  *  Divides the values in a vector vector
  * @param INT.
  *  Scalar to divide the vector to.
  * @return Vector2Int
  */
  FORCELINE Vector2Int
  operator/(int scalar) const noexcept;

  /*
  * @brief
  *  Checks if all the values in the vectors are the same.
  * @param Vector2Int
  * @return bool
  *  Returns true if both values are the same.
  */
  FORCELINE bool
  operator==(const Vector2Int& value) const noexcept;

  /*
  * @brief
  *  Checks if any of the values inside a vector are different to this.
  * @param Vector2Int&
  * @return true
  *  Returns true if any of the values are different.
  */
  FORCELINE bool
  operator!=(const Vector2Int& vector) const noexcept;

};

// Method definitions remain inside the namespace
FORCELINE Vector2Int&
Vector2Int::operator+=(const Vector2Int& vector) noexcept {
  x += vector.x;
  y += vector.y;
  return *this;
}

FORCELINE Vector2Int&
Vector2Int::operator-=(const Vector2Int& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
  return *this;
}

FORCELINE Vector2Int&
Vector2Int::operator*=(int scalar) noexcept {
  x *= scalar;
  y *= scalar;
  return *this;
}

FORCELINE Vector2Int&
Vector2Int::operator/=(int scalar) noexcept {
  x /= scalar;
  y /= scalar;
  return *this;
}

FORCELINE Vector2Int
Vector2Int::operator* (int scalar) const noexcept {
  return Vector2Int(x * scalar, y * scalar);
}

FORCELINE Vector2Int
Vector2Int::operator+(const Vector2Int& vector) const noexcept {
  return Vector2Int(x + vector.x, y + vector.y);
}

FORCELINE Vector2Int
Vector2Int::operator-(const Vector2Int& vector) const noexcept {
  return Vector2Int(x - vector.x, y - vector.y);
}

FORCELINE Vector2Int
Vector2Int:: operator/(int scalar) const noexcept {
  return Vector2Int(x / scalar, y / scalar);
}

FORCELINE bool
Vector2Int::operator==(const Vector2Int& vector) const noexcept {
  return x == vector.x && y == vector.y;
}


FORCELINE bool
Vector2Int::operator!=(const Vector2Int& vector) const noexcept {
  return x != vector. x || y != vector.y;
}

} 