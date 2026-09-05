#pragma once

namespace bowEngineSDK
{
class PlatformMath
{
public:
  /*
  * @brief Default contructor for platformMath
  */
   PlatformMath() = default;
  
  /*
  * @brief Default destructor for platformMath
  */
   ~PlatformMath() = default;

  /*
  * @brief Calculates the cosine of an angle
  * @param Angle, The angel is in radians
  * @return The cousine of an angle
  */
   static float
   cos(float angleInRadians);
};
}