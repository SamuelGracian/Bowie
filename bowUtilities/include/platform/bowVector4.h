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
  *  Constructor fom a vector 2.
  //*/
  //Vector4(Vector2&,float Z, float W);

  ///*
  //* @brief
  //*  Constructor from a vector 3.
  //*/
  //Vector4(Vector3&, float W);
  
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
  normalize()const;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  float x;
  float y;
  float z;
  float w;
};
}