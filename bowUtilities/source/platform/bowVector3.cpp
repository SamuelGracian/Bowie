#include "bowVector3.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector3::Vector3(float X, float Y, float Z)
  :x(X),
   y(Y),
   z(Z) {}

Vector3::Vector3(const float values[3])
  :x(values[0]),
   y(values[1]),
   z(values[2]) {}

Vector3::Vector3(const Vector2& vector, float Z)
  :x(vector.x),
   y(vector.y),
   z(Z)
{}

Vector3::Vector3(const Vector3& vector)
  :x(vector.x),
   y(vector.y),
   z(vector.z)
{}

Vector3
Vector3::cross(const Vector3& vector) const {
  return Vector3 (y * vector.z - z * vector.y,
                  z * vector.x - x * vector.z,
                  x * vector.y - y * vector.x);
}

float
Vector3::dot(const Vector3& vector) const {
  return (x * vector.x + y * vector.y + z * vector.z);
}

float
Vector3::magnitude() const {
  return Math::sqrt(sqrMagnitude());
}

float
Vector3::sqrMagnitude()const {
  return (Math::pow(x, 2) + Math::pow(y, 2) + Math::pow(z, 2));
}

float
Vector3::distance(const Vector3& vector) const {
  return Math::sqrt(sqrDistance(vector));
}

float
Vector3::sqrDistance(const Vector3& vector) const {
  const float deltaX = x - vector.x;
  const float deltaY = y - vector.y;
  const float deltaZ = z - vector.z;

  return (Math::pow(deltaX, 2) + Math::pow(deltaY, 2) + Math::pow(deltaZ, 2));
}

Vector3
Vector3::normalize() const {
  const float invMag = 1 / magnitude();
  return Vector3(x * invMag, y * invMag, z * invMag);
}

}