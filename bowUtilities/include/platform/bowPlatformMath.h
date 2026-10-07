#pragma once

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT PlatformMath
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

  /**
   * @brief Calculates the cosine of an angle
   * @param Angle, The angle is in radians
   * @return The cousine of an angle
  */
  static float
  cos(float angleInRadians);

  /**
   *@brief Calculates the Sin of an angle.
   @param Angle, The angle is in radians.
   @return The sin of an angle.
  */
  static float 
  sin(float angleInRadians);

  /**
    *@brief Calculates the tangent of an angle in radians.
    *@param angle. The angle is in radians.
    *@return The tangent fo an angle.
  */
  static float 
  tan(float angleInRadians);

   /**
    * @brief Computes the square root of a given number
    * @param value, value to compute
   *  PLS BE SPECIFFIC WITH THE FLOAT VALUE TO NOT USE THE INT VERSION.
    * @return float, The result of the square root of the value
   */
  static float
  sqrt(float value);

  /*
  * @brief
  *  Computes the squr root of a given number, to keep it int uses.
  *  THIS FUNCTION IS NOT PRECISE, DO EXPECT LOSING DATA.
  * @param INT
  * @return INT
  *  Returns the largest int whose square root is less than or equal to the param.
  */
  static int32
  sqrt(int32 value);

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

  /**
  * @brief Computes the arc tangent of a value.
  * @param angle
  * @return The arctangent of an angle
  */
  static float
  atan(float angleInRadians);

  /**
  * @brief Computes the arcsin of an angle.
  * @param Angle in radians, Only takes values between -1 and 1.
  * @return The Arc sin of an angle.
  */
  static float
  asin(float angleInRadians);

  /**
  * @brief Computes the linear interpolation between A and B, if the parameter T
  * is inside [ 0,1 ] (the linear interpolation otherwise) the result of a+t(b-a)
  * with accounting for floating point calculation imprecision.
  * @param A,B,T floating point or interger values;
  * @return A+T(B-A)
  */
  static float
  lerp(float valueA, float vaalueB, float valueT);

  /**
  * @brief  Clamps a variable to a given range
  * @param valueA, the value to clamp, minValue, maxValue the boundries to clamp A to
  * @return, reference to minValue if A is less than minValue,
  * reference to maxValue if maxValue is less than A, otherwise reference to A
  */
  static float
  clamp(float valueA, float minValue, float maxValue);

  static const float PI;

  /*
  * @brief 0.000001
  */
  static const float SMALL_NUMBER;

  /*
  * @brief 0.0001
  */
  static const float KINDA_SMALL_NUMBER;
};
}