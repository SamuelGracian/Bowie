/************************************************************************/
/**
 * @file bowMatrix.h
 * @author Samuel G
 * @date 24/09/2026
 *
 * Coordinates being X = front, Z = up, Y = right
 *
 */
 /************************************************************************/
#pragma once

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
class Vector3;
class Vector4;
class BOW_UTILITIES_EXPORT Matrix4
{
public:
  /********************************************/
  /*  CONSTRUCTORS, DESTRUCTORS  */
  /********************************************/

  /*
  * @brief
  *  Defult constructor.
  *  Row mayor matrix.
  */
  Matrix4() = default;

  /*
  * @brief
  *  Constructs a matrix from individual values.
  *  Row mayor matrix.
  */
  Matrix4(float M00, float M01, float M02, float M03,
          float M10, float M11, float M12, float M13,
          float M20, float M21, float M22, float M23,
          float M30, float M31, float M32, float M33);

  /*
  * @brief
  *  Copy constructor.
  */
  Matrix4(const Matrix4& copy) = default;

  /*
  * @brief
  *  Default destructor.
  */
  ~Matrix4() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /*
  * @brief
  *  Set this matrix as an identity matrix.
  *  With the values in diagonal as 1, and the rest 0.
  * @param NONE
  * @return NONE
  */
  void
  setIdentity();

  /*
  * @brief
  *  Changes the order of the matrix from mxn to nxm. Changing it rows
  *  for its columns
  * @param NONE
  * @return MATRIX4
  *  Rreturns the transposed matrix.
  */
  NODISCARD Matrix4
  transposed() const;

  /*
  * @brief
  * @param NONE
  * @return
  */
  NODISCARD float
  getDeterminant() const;

  /*
  * @brief
  *  Transform a 3D position represented as a vector3
     and transform it to a vector4.
     To make the conversion this function reads the translation from the last row.
  * @param VECTOR3&
  * @return VECTOR4
  *  Returns a vector4 with the translation from the matrix.
  */
  NODISCARD Vector4
  transformPosition(const Vector3& vector) const;

  /*
  * @brief
  *  Transform a vector3, ignoring the translation from the matrix. 
  * @param VECTOR3&
  * @return VECTOR4
  *  Returns a transformed vector4 witout the translation from the matrix.
  */
  NODISCARD Vector4
  transformVector(const Vector3& vector) const;

  /*
  * @brief
  *  Calculates the inverse matrix.
  * @param NONE
  * @return MATRIX4
  *  Returns the inversed matrix as a vector4.
  */
  NODISCARD Matrix4
  getInverse() const;

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
  Matrix4&
  operator*=(const Matrix4& other);

  /*
  * @brief
  *  Multiplies this matrix by a given value.
  * @param FLOAT
  * @return
  *  A reference to this matrix after the multiplication.
  */
  Matrix4&
  operator*=(float value);

  /*
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the division.
  */
  NODISCARD Matrix4&
  operator/=(const Matrix4& other);

  /*
  * @brief
  *  Adds another matrix to this matrix
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the addition.
  */
  NODISCARD Matrix4&
  operator+=(const Matrix4& other);

  /*
  * @brief
  *  Substracts another matrix to this matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the substraction.
  */
  NODISCARD Matrix4&
  operator-=(const Matrix4& other);

  /*
  * @brief
  *  Checks if the values between two matrix are diferent from each other.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix are diferent in any of its values.
  */
  NODISCARD bool
  operator!=(const Matrix4& other) const;

  /*
  * @brief
  *  Checks if the values between two matrix are the same.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix have the same values.
  */
  NODISCARD bool
  operator==(const Matrix4& other) const;

  /*
  * @brief
  *  Substract this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix 
  */
  NODISCARD Matrix4
  operator-(const Matrix4& other) const;

  /*
  * @brief
  *  Adds another matrix to this matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new class with the subtracted values.
  */
  NODISCARD Matrix4
  operator+(const Matrix4& other) const;

  /*
  * @brief
  *  Multiplies this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  Matrix4
  operator*(const Matrix4& other) const;

  /*
  * @brief
  *  Multiplies this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  Matrix4
  operator*(float value) const;

  /*
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  Matrix4
  operator/(const Matrix4& other) const;

  /*
  * @brief
  *  Divides this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  Matrix4
  operator/(float value) const;

  /*
  * @brief
  *  Copies the data from another matrix to this matrix.
  * @param MATRIX& 
  * @return
  *  A reference to this matrix, with the copied data from the param.
  */
  Matrix4&
  operator=(const Matrix4& origin) = default;

  /********************************************/
  /*  STATIC MEMBERS  */
  /********************************************/
  static const Matrix4 IDENTITY;
  static const Matrix4 ZERO;

  /********************************************/
  /*  MEMBERS  */
  /********************************************/
  float data[4][4];
};
}
