/*
* @date 24/09/26
*   Base class for matrix4x4
*
* Coordinate system begin X = front, Z = Up, Y = Right.
*/

#pragma once

#include <array>

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class BOW_UTILITIES_EXPORT bowMatrix
{
public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS              */
  /********************************************/

  /*
  * @brief
  * Constructs a zero-initialized 4x4 matrix.
  */
  bowMatrix() noexcept;

  /*
  * @brief
  * Constructs a matrix from individual values.
  */
  bowMatrix(float M00, float M01, float M02, float M03,
            float M04, float M05, float M06, float M07,
            float M08, float M09, float M10, float M11,
            float M12, float M13, float M14, float M15);

  /*
  * @brief
  * Constructs a matrix from an array.
  */
  explicit bowMatrix(const std::array<float, 16>& values);

  /*
  * @brief
  * Default destructor.
  */
  ~bowMatrix() = default;

  /********************************************/
  /*  METHODS                                */
  /********************************************/

  /*
  */
  void
  setIdentity();

  /*
  * @brief
  *  Rreturns the transposed matrix.
  */
  [[nodiscard]] bowMatrix
  transposed() const;

  /*
  * @brief
  * 
  */
  [[nodiscard]] bowMatrix& 
  getTransposed() const noexcept;

  /*
  * @brief
  * Creates an identity matrix.
  */
  [[nodiscard]] static bowMatrix 
  identity() noexcept;


  [[nodiscard]] float
  getDeterminant() const;

  /*
  * @brief
  * Provides read-only access to the matrix values.
  */
  [[nodiscard]] const std::array<float, 16>& 
  values() const noexcept;

  std::array<float, 16> matrixV;
};
}