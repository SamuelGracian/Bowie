#include "bowPlatformMath.h"

#include <cmath>

namespace bowEngineSDK
{

float
PlatformMath::cos(float angleInRadians) {
  return std::cos(angleInRadians);
}

float
PlatformMath::sin(float angleInRadians){
  return std::sin(angleInRadians);
}

float 
PlatformMath::sqrt (float value){
  return std::sqrt(value);
}

float
PlatformMath::invSqrt(float value){
  return 1.0f / std::sqrt(value);
}

float 
PlatformMath::pow (float value, const float vPow){
  return std::pow(value, vPow);
}
}