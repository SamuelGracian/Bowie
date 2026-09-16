#include "bowVector2.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector2::Vector2(float X, float Y)
  : m_x(X),
    m_y(Y) 
{}

Vector2::Vector2(const float values[2])
  : m_x(values[0]),
    m_y(values[1]) 
{}

float
Vector2::dot(const Vector2& vector2)const {
  return (m_x * vector2.m_x) + (m_y * vector2.m_y);
}

float
Vector2::cross(const Vector2& vector2)const {
  return (m_x * vector2.m_y) - (m_y * vector2.m_x);
}

float
Vector2::magnitude()const {
  return Math::sqrt(sqrMagnitude());
}

float
Vector2::sqrMagnitude()const {
  return Math::pow(m_x, 2) * Math::pow(m_y, 2);
}

float
Vector2::distance(const Vector2& vector)const {
  return Math::sqrt(sqrDistance(vector));
}

float
Vector2::sqrDistance(const Vector2& vector) const {
  const float deltaX = m_x - vector.m_x;
  const float deltaY = m_y - vector.m_y;
  return (deltaX * deltaX) + (deltaY * deltaY);
}

Vector2
Vector2::normalize() const {
  const float invMag = 1 / magnitude();
  return Vector2(m_x * invMag, m_y * invMag);
}

float
Vector2::getXValue()const {
  return m_x;
}

float
Vector2::getYValue()const {
  return m_y;
}
}