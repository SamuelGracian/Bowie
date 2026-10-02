/************************************************************************/
/**
 * @file bowSphere.h
 * @author Samuel G
 * @date 1/10/2026
 * @brief Class to represent a 3D sphere.
 */
 /************************************************************************/
#pragma once


#include "bowVector3.h"

namespace bowEngineSDK
{
class Vector3;
class BOW_UTILITIES_EXPORT Sphere
{
public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Default destructor.
  * @param NONE
  */
  Sphere() = default;

  /*
  * @brief
  *  Cosntructor with given values.
  * @param VECTOR3&, FLOAT
  */
  Sphere(const Vector3& centerPoint, float _radius);

  /*
  * @brief
  *  Constructor with given values, builds the vector from scratch
  *  using the params to build it.
  * @param FLOAT, FLOAT, FLOAT, FLOAT, FLOAT
  */
  Sphere(float X, float Y, float Z, float _radius);

  /*
  * @brief
  *  Default destructor.
  */
  ~Sphere() = default;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  Vector3 center;
  float radius;

};

}
