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

   /**
    * @brief Computes the square root of a given number
    * @param value, value to compute
    * @return float, The result of the square root of the value
   */
  static float
  sqrt(float value);

   /**
    * @brief inverse square root of a value
    * @param value, value to compute
    * @return float, The inverse square root of a vlue.
   */
  static float 
  invSqrt (float value);

  /**
   * @brief computes pow of a given value
   * @param value, Value to apply pow
   * @return float, The calculated pow.
  */
  static float
  pow(float value, const float vPow);
};
}