#include "bowPlane.h"

namespace bowEngineSDK
{
  Plane::Plane(const Vector4& vector)
    : Vector3(vector.x, vector.y, vector.z), w(vector.w)
  {}

  Plane::Plane(const Vector3& vector, float W)
    : Vector3(vector), w(W)
  {}

  Plane::Plane(float X, float Y, float Z, float W)
    : Vector3(X, Y, Z), w(W)
  {}

  Plane::Plane(const Vector3& point, const Vector3& normal)
    : Vector3(normal), w(-point.dot(normal))
  {}

}
