#include "bowPlatformVector2.h"

namespace bowEngineSDK
{
Vector2::Vector2(float X, float Y)
  : m_x(X),
   m_y(Y){
}

float
Vector2::dot(const Vector2& vector2) const {
  return (m_x * vector2.m_x) + (m_y * vector2.m_y);
}
}