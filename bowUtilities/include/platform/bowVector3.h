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
  *  Cosntructor from vector2.
  */
  //Vector3(Vector2 vector, float Z);

  /*
  * @brief
  *  Default destructor.
  */
  ~Vector3() = default;

  /*
  */
  float
  dot(Vector3& vector);
  
  /*
  * @brief
  * Calculates the cross product from 2 given vectors.
  * @param Vector3
  * 
  * @return float
  * Returns the cross product from 2 vectors.
  */
  float
  cross(Vector3& vector);

  /*
  */
  float
  magnitude()const;
  
  /*
  */
  float
  sqrMagnitude()const;

  /*
  */
  float
  distance(Vector3 vector);

  /*
  */
  float
  sqrDistance(Vector3 vector);

private:
  float m_x;
  float m_y;
  float m_z;
};

}