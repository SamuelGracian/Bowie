#include "bowVector2_int.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector2_int::Vector2_int(int X, int Y)
  : x(X),
    y(Y)
{}

Vector2_int::Vector2_int(const int vector[2])
  :x(vector[0]),
   y(vector[1])
{}

int
Vector2_int::dot(const Vector2_int& vector) const {
  return (x * vector.x) + (y * vector.y);
}

int
Vector2_int::cross(const Vector2_int& vector) const {
  return (x * vector.y) - (y * vector.x);
}

float
Vector2_int::magnitude() const {
  return Math::sqrt(sqrMagitude());
}

int
Vector2_int::sqrMagitude() const {
  return Math::pow(x, 2) * Math::pow(y, 2);
}

int
Vector2_int::distance(const Vector2_int& vector) const {
  return Math::sqrt(sqrDistance(vector);
}

int
Vector2_int::sqrDistance(const Vector2_int& vector) const {
  const int deltaX = x - vector.x;
  const int deltaY = y - vector.y;
  return (deltaX * deltaX) + (deltaY * deltaY);
}

//Vector2
//Vector2_int::normalize() const {
//  const float invMag = 1 / magnitude();
//  return Vector2(x * invMag, y * invMag);
//}

}