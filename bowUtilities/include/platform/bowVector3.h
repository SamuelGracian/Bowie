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
  *  Cosntructor from vector2.
  */
  //Vector3(const Vector2 vector, float Z);

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
  dot(const Vector3& vector) const ;
  
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
  magnitude()const;
  
  /*
  * @brief
  * @param NONE
  * @return float
  */
  float
  sqrMagnitude()const;

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

  float x;
  float y;
  float z;
};

}