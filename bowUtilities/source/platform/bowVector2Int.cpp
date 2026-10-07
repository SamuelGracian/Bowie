#include "bowVector2Int.h"

#include "bowPlatformMath.h"

namespace bowEngineSDK
{
Vector2Int::Vector2Int(int32 X, int32 Y)
  : x(X),
    y(Y)
{}

Vector2Int::Vector2Int(const int32 vector[2])
  :x(vector[0]),
   y(vector[1])
{}

int32
Vector2Int::dot(const Vector2Int& vector) const {
  return (x * vector.x) + (y * vector.y);
}

int32
Vector2Int::cross(const Vector2Int& vector) const {
  return (x * vector.y) - (y * vector.x);
}

int32
Vector2Int::magnitude() const {
  int32 sqrMag = sqrMagnitude();
  return PlatformMath::sqrt(sqrMag);
}

int32
Vector2Int::sqrMagnitude() const {
  return (( x * x ) * ( y * y ));
}

int
Vector2Int::distance(const Vector2Int& vector) const {
  return PlatformMath::sqrt(sqrDistance(vector));
}

int32
Vector2Int::sqrDistance(const Vector2Int& vector) const {
  const int32 deltaX = x - vector.x;
  const int32 deltaY = y - vector.y;
  return (deltaX * deltaX) + (deltaY * deltaY);
}

//Vector2
//Vector2Int::normalize() const {
//  const float invMag = 1 / magnitude();
//  return Vector2(x * invMag, y * invMag);
//}

}