/************************************************************************/
/**
 * @file bowFigureHelper.h
 * @author Samuel G
 * @date 02/10/2026
 * @brief   Class to represent a three dimensional plane.
 */
 /************************************************************************/
#pragma once 

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class AAB;
class Plane;
class Sphere;
class Vector3;

class BOW_UTILITIES_EXPORT FigureHelper
{
public:
  FigureHelper() = default;

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  Sphere and sphere override
  * @param CONST SPHERE, CONST SPHERE
  * @return BOOL
  *  Returns true if theres an intersection between the spheres.
  */
  static bool
  Intersects(const Sphere& sphere1, const Sphere& sphere2);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  sphere and point override
  * @param CONST SPHERE, CONST POINT
  * @return BOOL
  */
  static bool
  Intersects(const Sphere& sphere, const Vector3& point);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  Sphere and plane override
  * @param CONST SPHERE, CONST PLANE
  * @return BOOL
  */
  static bool
  Intersects(const Sphere& sphere, const Plane& plane);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  Sphere nad AAB oveerride
  * @param CONST SPHERE, CONST AAB
  * @return BOOL
  */
  static bool
  Intersects(const Sphere& sphere, const AAB& box);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  Plane and plane override
  * @param CONST PLANE, CONST PLANE
  * @return
  */
  static bool
  Intersects(const Plane& plane1, const Plane& plane2);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  Plane and point
  * @param CONST PLANE, CONST VECTOR3
  * @return BOOL
  *  Returns true if theres an intersection between the plane and the point.
  */
  static bool
  Intersects(const Plane& plane, const Vector3& point);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  AAB and plane override.
  * @param CONST BOX, CONST PLANE.
  * @return BOOL
  */
  static bool
  Intersects(const AAB& box, const Plane& plane);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  AAB and AAB override
  * @param AAB&, AAB&
  * @return BOOL
  */
  static bool
  Intersects(const AAB& box1, const AAB& box2);

  /*
  * @brief
  *  Checks if theres any intersection betweeen two shapes.
  *  AAB and point override
  * @param CONST AAB, CONST VECTOR3
  * @return BOOL
  */
  static bool
  Intersects(const AAB& box, const Vector3& point);

};

}
// namespace bowEngineSDK