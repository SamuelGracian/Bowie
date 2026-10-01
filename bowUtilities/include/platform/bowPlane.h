/************************************************************************/
/**
 * @file bowPlane.h
 * @author Samuel G
 * @date 01/10/2026
 * @brief   Class to represent a three dimensional plane.
 */
 /************************************************************************/
#pragma once

#include "bowVector3.h"
#include "bowVector4.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT Plane : public Vector3
{
public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Default constructor.
  */
  Plane() = default;

  /*
  * @brief
  *  Constuctor from a vector 4.
  */
  explicit Plane(const Vector4& vector);

  /*
  * @brief
  *  Constructor from a vector3.
  * @param VECTOR3&, FLOAT
  */
  Plane(const Vector3& vector, float W);

  /*
  * @brief
  *  Constructor from given values.
  * @param FLOAT, FLOAT, FLOAT, FLOAT
  *  x, y, z, w
  *  where w == 1 is for a vector, w == 0 is for a vector/ direction.
  */
  Plane(float X, float Y, float Z, float W);

  /*
  * @brief
  *  Constructor from a point inside the plane, and the normal of the plane.
  * @param VECTOR3&, VECTOR3&.
  *  point = any point inside the plane, normal = normal of the plane.
  */
  Plane(const Vector3& point, const Vector3& normal);

  /*
  * @brief
  *  Default destructor.
  */
  ~Plane() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/


  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  float w;
};
}
