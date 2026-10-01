#include "bowPlane.h"

namespace bowEngineSDK
{
  Plane::Plane(const Vector4& vector)
    : Vector3(vector), w(vector.w)
  {}

  Plane::Plane(const Vector3& vector, float W)
    : Vector3(vector), w(W)
  {}

  Plane::Plane(float X, float Y, float Z, float W)
    : Vector3(X, Y, Z), w(W)
  {}

}
