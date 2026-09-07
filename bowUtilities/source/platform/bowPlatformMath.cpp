#include "bowPlatformMath.h"

#include <cmath>

namespace bowEngineSDK
{

float
PlatformMath::cos(float angleInRadians) {
  return std::cos(angleInRadians);
}


float 
squrt (float value){
  return std::sqrt(value);
}

float
invSqrt(float value){
  return 1.0f / std::sqrt(value);
}
}