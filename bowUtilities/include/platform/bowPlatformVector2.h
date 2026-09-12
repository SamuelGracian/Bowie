#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK{
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
    Default destructor.
 */
  ~Vector2() = default;

  /*
  * @brief
     Dot product from two vector 2.
  * @param Vector2
     Vector2 The vector2 to calculate the dot product with.
  * @return float
     float The dot product from this vector2 and the param.
  */
  float
  dot(Vector2& vector2);

  /*
  * @brief 
  *  Calculates the cross product from 2 vectors.
  * @Param Vector2
  * @return float
  *  Corss product from 2 vectors.
  */
  float
  cross(Vector2& vector2);

  /*
  * @brief
  *  Calculates the magnitude (lenght of the vector).
  * @return float
  *  The lenght of the vector.
  */
  float
  magnitude() const;

  /*
  * @brief
  *  Calculates the square magnitude (lengh) of this vector.
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
  * 
  */
  float
  distance(const Vector2 vector);

  /*
  * @brief
  *  Calculates the square distence betweeen 2 vectors without using sqrt.
  * @param Vector2
  *  The vector to calculate the square distance to.
  * @return float
  *  The square distance between this vector and the one given as param.
  */
  float
  sqrDistance(Vector2 vector) const;

  /*
  * @brief
  *  Normalize this vector.
  * @return
  *  This as a normalized vector.
  */
  Vector2
  normalize()const;

private:
  float m_x;
  float m_y;

};
}