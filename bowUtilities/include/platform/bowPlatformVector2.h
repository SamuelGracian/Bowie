#pragma once

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK{
class BOW_UTILITIES_EXPORT Vector2
{
public:

  /*
  * @brief Defautl constructor.
  */
  Vector2() = default;

  /*
  * @brief Constructor with given values.
  */
  Vector2(float X, float Y);

 /*
 * @brief Default destructor.
 */
  ~Vector2() = default;

  /*
  * @brief Dot product from two vector 2.
  * @param Vector2 The vector2 to calculate the dot product with.
  * @return float The dot product from this vector2 and the param.
  */
  float
  dot(const Vector2& vector2) const;

private:
  float m_x;
  float m_y;

};
}