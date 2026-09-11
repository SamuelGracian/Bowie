#include "bowPlatformMath.h"

#include <cmath>
#include <algorithm>
#include <numbers>

namespace bowEngineSDK
{

const float
PlatformMath::PI = std::numbers::pi_v <float>;

const float
PlatformMath::SMALL_NUMBER = (1.e-6f);

const float
PlatformMath::KINDA_SMALL_NUMBER = (1.e-4f);

float
PlatformMath::cos(float angleInRadians) {
  return std::cos(angleInRadians);
}

float
PlatformMath::sin(float angleInRadians){
  return std::sin(angleInRadians);
}

float
PlatformMath::tan(float angleInRadians){
  return std::tan(angleInRadians);
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

float 
PlatformMath::atan(float angleInRadians) {
  return std::atan(angleInRadians);
}

float
PlatformMath::asin(float angleInRadians) {
  return std::asin(angleInRadians);
}

float
PlatformMath::lerp(float valueA, float valueB, float valueT) {
  return std::lerp(valueA, valueB, valueT);
}

float 
PlatformMath::clamp(float valueA, float minValue, float maxValue) {
  return std::clamp(valueA, minValue, maxValue);
}
}