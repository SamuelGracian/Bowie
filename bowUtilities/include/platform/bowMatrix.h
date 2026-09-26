#pragma once
#include<array>

#include"bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT bowMatrix
{
 public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Default constructor.
  */
  bowMatrix() = default;

  /*
  * @brief
  * Constructor from given values.
  */
  bowMatrix(float A1, float A2, float A3, float A4,
            float A5, float A6, float A7, float A8,
            float A9, float A10, float A11, float A12,
            float A13, float A14, float A15, float A16);

  /*
  * @brief
  *  Constructor from an array.
  */
  explicit bowMatrix(const std::array<float, 16> values);

  /*
  * @brief
  *  Default destructor.
  */
  ~bowMatrix() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
  * @param NONE
  * @return bowMatrix
  */
  bowMatrix
  transposed() const;

  /*
  * @brief
  * @param NONE
  * @return bowMatrix
  */
  bowMatrix
  identity() const;
  
  /*
  * @brief
  * @param NONE
  * @return
  */
  bowMatrix
  translation(float X, float Y, float Z) const;

  /********************************************/
  /*  OPERATORS  */
  /********************************************/



  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  std::array<float, 16> matrixV;
};
}