#pragma once

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
  * Row mayor matrix.
  * First index is the row, and the second is the column.
  */
  bowMatrix() = default;

  /*
  * @brief
  * Constructs a matrix from individual values.
  * Row mayor matrix.
  * First index is the row, and the second is the column.
  */
  bowMatrix(float M00, float M01, float M02, float M03,
            float M04, float M05, float M06, float M07,
            float M08, float M09, float M10, float M11,
            float M12, float M13, float M14, float M15);

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
  NODISCARD bowMatrix
  transposed() const;

  /*
  * @brief
  *
  */
  NODISCARD bowMatrix
  getTransposed() const noexcept;

  /*
  * @brief
  * Creates an identity matrix.
  */
  //[[nodiscard]] static bowMatrix
  //identity() noexcept;

  /*
  * @brief
  * @param NONE
  * @return
  */
  NODISCARD float
  getDeterminant() const;

  /*
  * @brief
  * @param VECTOR3&
  * @return VECTOR4
  */
  NODISCARD Vector4
  transformPosition(const Vector3& vector) const;

  /*
  * @brief
  * @param VECTOR3&
  * @return VECTOR4
  */
  NODISCARD Vector4
  transformVector(const Vector3& vector) const;


  NODISCARD bowMatrix
  getInverse() const;

  /*
  * @brief
  * Provides read-only access to the matrix values.
  */
  NODISCARD const float*
  getData() const noexcept;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/

  /*
  * Matrix values
  */
  float m_data[4][4];
  /********************************************/
  /*  OPERATORS  */
  /********************************************/

  /*
  * @brief
  *  Multplies this matrix by another matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the multiplication.
  */
  NODISCARD bowMatrix&
  operator*=(const bowMatrix& other);

  /*
  * @brief
  *  Multiplies this matrix by a given value.
  * @param FLOAT
  * @return
  *  A reference to this matrix after the multiplication.
  */
  NODISCARD bowMatrix&
  operator*=(float value);

  /*
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the division.
  */
  NODISCARD bowMatrix&
  operator/=(const bowMatrix& other);

  /*
  * @brief
  *  Adds another matrix to this matrix
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the addition.
  */
  NODISCARD bowMatrix&
  operator+=(const bowMatrix& other);

  /*
  * @brief
  *  Substracts another matrix to this matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the substraction.
  */
  NODISCARD bowMatrix&
  operator-=(const bowMatrix& other);

  /*
  * @brief
  *  Checks if the values between two matrix are diferent from each other.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix are diferent in any of its values.
  */
  NODISCARD bool
  operator!=(const bowMatrix& other);

  /*
  * @brief
  *  Checks if the values between two matrix are the same.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix have the same values.
  */
  NODISCARD bool
  operator==(const bowMatrix& other);

  /*
  * @brief
  *  Substract this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix 
  */
  NODISCARD bowMatrix
  operator-(const bowMatrix& other) const;

  /*
  * @brief
  *  Adds another matrix to this matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new class with the subtracted values.
  */
  NODISCARD bowMatrix
  operator+(const bowMatrix& other) const;

  /*
  * @brief
  *  Multiplies this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  NODISCARD bowMatrix
  operator*(const bowMatrix& other) const;

  /*
  * @brief
  *  Multiplies this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  NODISCARD bowMatrix
  operator*(float value) const;

  /*
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  NODISCARD bowMatrix
  operator/(const bowMatrix& other) const;

  /*
  * @brief
  *  Divides this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  NODISCARD bowMatrix
  operator/(float value) const;
};
}