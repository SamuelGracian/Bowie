#include "bowVector4.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector4::Vector4(float X, float Y, float Z, float W)
  :x(X),
   y(Y),
   z(Z),
   w(W)
{}

Vector4::Vector4(const float value [4])
  :x(value[0]),
   y(value[1]),
   z(value[2]),
   w(value[3])
{}

float
Vector4::dot(const Vector4& vector) const {
  return (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
}

Vector4
Vector4::cross(const Vector4& vector) const {
  return Vector4(
    (y * vector.z) - (z * vector.y),
    (z * vector.x) - (x * vector.z),
    (x * vector.y) - (y * vector.x),
    0.0f
  );
}

float
Vector4::sqrMagnitude() const {
  return Math::pow(x, 2) + Math::pow(y, 2) + Math::pow(z, 2) + Math::pow(w, 2);
}

float
Vector4::magnitude() const {
  return Math::sqrt(sqrMagnitude());
}

float
Vector4::sqrDistance(const Vector4& vector) const {
  const float deltaX = x - vector.x;
  const float deltaY = y - vector.y;
  const float deltaZ = z - vector.z;
  const float deltaW = w - vector.w;

  return (deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ) + (deltaW * deltaW);
}

float
Vector4::distance(const Vector4& vector) const {
  return Math::sqrt(sqrDistance(vector));
}

Vector4
Vector4::normalize() const {
  const float lengthSquared = sqrMagnitude();

  if (lengthSquared <= 0.0f) {
    return Vector4();
  }

  const float inverseLength = Math::invSqrt(lengthSquared);

  return Vector4(x * inverseLength, y * inverseLength, z * inverseLength, w * inverseLength);
}

}