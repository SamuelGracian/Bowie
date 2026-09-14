#include "bowPlatformVector2.h"

#include "bowMath.h"

namespace bowEngineSDK
{
Vector2::Vector2(float X, float Y)
  : m_x(X),
   m_y(Y){
}

Vector2::Vector2(const float values[2])
  : m_x(values[0]),
    m_y(values[1]){

}

float
Vector2::dot(Vector2& vector2){
  return (m_x * vector2.m_x) + (m_y * vector2.m_y);
}

float
Vector2::cross(Vector2& vector2) {
  return (m_x * vector2.m_y) - (m_y * vector2.m_x);
}

float
Vector2::magnitude()const{
  return Math::sqrt(sqrMagnitude());
}

float
Vector2::sqrMagnitude()const{
  return Math::pow(m_x, 2) * Math::pow(m_y, 2);
}

float
Vector2::distance(const Vector2 vector)const{
  return Math::sqrt(sqrDistance(vector));
}

float
Vector2::sqrDistance(Vector2 vector) const{
  const float deltaX = m_x - vector.m_x;
  const float deltaY = m_y - vector.m_y;
  return (deltaX * deltaX) + (deltaY * deltaY);
}

Vector2
Vector2::normalize() const {
  const float magnitude = Math::sqrt(Math::pow(m_x,2) + (Math::pow(m_y,2)));

  Vector2 normalizedVector;
  normalizedVector.m_x = m_x / magnitude;
  normalizedVector.m_y = m_y / magnitude;

  return normalizedVector;
}

float
Vector2::GetXValue()const{
  return m_x;
}

float
Vector2::GetYValue()const {
  return m_y;
}

void
Vector2::UpdateValues(float newX, float newY) {
  m_x = newX;
  m_y = newY;
}

}