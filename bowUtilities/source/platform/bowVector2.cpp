#include "bowVector2.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector2::Vector2(float X, float Y)
  : x(X),
    y(Y) 
{}

Vector2::Vector2(const float values[2])
  : x(values[0]),
    y(values[1]) 
{}

float
Vector2::dot(const Vector2& vector2)const {
  return (x * vector2.x) + (y * vector2.y);
}

float
Vector2::cross(const Vector2& vector2)const {
  return (x * vector2.y) - (y * vector2.x);
}

float
Vector2::magnitude()const {
  return Math::sqrt(sqrMagnitude());
}

float
Vector2::sqrMagnitude()const {
  return Math::pow(x, 2) * Math::pow(y, 2);
}

float
Vector2::distance(const Vector2& vector)const {
  return Math::sqrt(sqrDistance(vector));
}

float
Vector2::sqrDistance(const Vector2& vector) const {
  const float deltaX = x - vector.x;
  const float deltaY = y - vector.y;
  return (deltaX * deltaX) + (deltaY * deltaY);
}

Vector2
Vector2::normalize() const {
  const float invMag = 1 / magnitude();
  return Vector2(x * invMag, y * invMag);
}

float
Vector2::getXValue()const {
  return x;
}

float
Vector2::getYValue()const {
  return y;
}
}