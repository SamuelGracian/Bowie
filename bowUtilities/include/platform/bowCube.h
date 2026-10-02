/************************************************************************/
/**
 * @file bowCube.h
 * @author Samuel G
 * @date 01/10/2026
 * @brief Represents a cube allign in both axis.
 */
 /************************************************************************/
#pragma once

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class Vector3;
class BOW_UTILITIES_EXPORT Cube
{
public:

  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Default constructor.
  * @param NONE
  */
  Cube() = default;

  /*
  * @brief
  *  Constructor with given vectors.
  * @param CONST VECTOR3&, CONST VECTOR3&
  *  min = minumm point in the cube, max = max point in the cube.
  */
  Cube(const Vector3& min, const Vector3& max);

  /*
  * @brief
  *  Default constructor.
  * @param NONE.
  */
  ~Cube() = default;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  Vector3 minPoint;
  Vector3 maxPoint;
};
}
