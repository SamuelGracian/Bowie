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
class Vector3;
class Vector4;
class BOW_UTILITIES_EXPORT bowMatrix
{
public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  * Constructs a zero-initialized 4x4 matrix.
  */
  bowMatrix() = default;

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
  /*  METHODS  */
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

  /*
  * @brief
  * @param NONE
  * @return
  */
  [[nodiscard]] float
  getDeterminant() const;

  /*
  * @brief
  * @param VECTOR3&
  * @return VECTOR4
  */
  [[nodiscard]] Vector4
  transformPosition(const Vector3& vector) const;

  /*
  * @brief
  * @param VECTOR3&
  * @return VECTOR4
  */
  [[nodiscard]] Vector4
  transformVector(const Vector3& vector) const;

  /*
  * @brief
  * Provides read-only access to the matrix values.
  */
  [[nodiscard]] const std::array<float, 16>& 
  values() const noexcept;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  std::array<float, 16> matrixV;

  /********************************************/
  /*  OPERATORS  */
  /********************************************/

  [[nodiscard]] FORCELINE void
  operator*= (const bowMatrix& other);

  [[nodiscard]] FORCELINE bowMatrix&
  operator*= (float value);

  [[nodiscard]] FORCELINE  void
  operator/= (const bowMatrix& other);

  [[nodicard]] FORCELINE void
  operator+= (const bowMatrix& other);

  [[nodiscard]] FORCELINE void
  operator-= (const bowMatrix& other);

  [[nodiscard]] FORCELINE bool
  operator!= (const bowMatrix& other);

  [[nodiscard]] FORCELINE bool
  operator== (const bowMatrix& other);

  [[nodiscard]] FORCELINE bowMatrix
  operator- (const bowMatrix& other) const;

  [[nodisacard]] FORCELINE bowMatrix
  operator+ (const bowMatrix& otehr) const;

  [[nodiscard]] FORCELINE bowMatrix
  operator* (const bowMatrix& other) const;

  [[nodiscard]] FORCELINE bowMatrix
  operator* (float value) const;

  [[nodiscard]] FORCELINE bowMatrix
  operator/ (const bowMatrix& other) const;

  [[nodiscard]] FORCELINE bowMatrix
  operator/ (float value) const;
};
}