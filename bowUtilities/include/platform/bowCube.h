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
#include "bowSTDHeaders.h"
#include "bowVector3.h"

namespace bowEngineSDK
{
class Vector3;
class BOW_UTILITIES_EXPORT AAB
{
public:

  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Axis Align Box Default constructor.
  * @param NONE
  */
  AAB() = default;

  /*
  * @brief
  *  Constructor with given vectors.
  * @param CONST VECTOR3&, CONST VECTOR3&
  *  min = minumm point in the cube, max = max point in the cube.
  */
  AAB(const Vector3& min, const Vector3& max);

  /*
  * @brief
  *  Default constructor.
  * @param NONE.
  */
  ~AAB() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
  *  Gets the center point of the cube.
  * @param NONE
  * @return VECTOR3
  *  Returns a vector representing the center of the cube.
  */
  Vector3
  getCenter() const;

  /*
  * @brief
  *  Get the size of the cube
  * @param NONE
  * @return VECTOR3
  *  Returns a vector where every value represents the size in each axis.
  */
  Vector3
  getSize() const;

  /*
  * @brief
  *  Moves the box to another location.
  * @param VECTOR3&
  *  Position to move the box to 
  * @return NONE
  */
  void
  moveTo(const Vector3& position);

  /*
  * @brief
  */
  void
  updatePoints();

  Array<float, 24>
  getCorners() const;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  Vector3 minPoint;
  Vector3 maxPoint;

  Array<float, 24> points;
};
}
