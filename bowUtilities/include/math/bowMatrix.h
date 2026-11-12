/************************************************************************/
/**
 * @file bowMatrix.h
 * @author Samuel G
 * @date 24/09/2026
 *
 * Coordinates being X = right, Z = backward, Y = up
 *  Right handed matrix
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

  /**
  * @brief
  *  Default constructor.
  *  Row mayor matrix.
  */
  Matrix4() = default;

  /**
  * @brief
  *  Constructs a matrix from individual values.
  *  Row mayor matrix.
  * @param FLOAT 
  *  16 float values.
  */
  Matrix4(float M00, float M01, float M02, float M03,
          float M10, float M11, float M12, float M13,
          float M20, float M21, float M22, float M23,
          float M30, float M31, float M32, float M33);

  /**
  * @brief
  *  Copy constructor.
  * @param copy: matrix to copy.
  */
  Matrix4(const Matrix4& copy) = default;

  /**
  * @brief
  *  Default destructor.
  */
  ~Matrix4() = default;

  /********************************************/
  /*  METHODS  */
  /********************************************/

  /**
  * @brief
  *  Set this matrix as an identity matrix.
  *  With the values in diagonal as 1, and the rest 0.
  * @param none
  * @return none
  */
  void
  setIdentity();

  /**
  * @brief
  *  Changes the order of the matrix from mxn to nxm. Changing it rows
  *  for its columns
  * @param none
  * @return
  *  Returns the transposed matrix.
  */
  NODISCARD Matrix4
  transposed() const;

  /**
  * @brief
  * @param none
  * @return
  */
  NODISCARD float
  getDeterminant() const;

  /**
  * @brief
  *  Transform a 3D position represented as a vector3
     and transform it to a vector4.
     To make the conversion this function reads the translation from the last row.
  * @param vector: vector to transform.
  * @return
  *  Returns a vector4 with the translation from the matrix.
  */
  NODISCARD Vector4
  transformPosition(const Vector3& vector) const;

  /**
  * @brief
  *  Transform a vector3, ignoring the translation from the matrix. 
  * @param vector: vector to be used to apply the transformation.
  * @return 
  *  Returns a transformed vector4 without the translation from the matrix.
  */
  NODISCARD Vector4
  transformVector(const Vector3& vector) const;

  /**
  * @brief
  *  Calculates the inverse matrix.
  * @param none
  * @return MATRIX4
  *  Returns the inverse matrix as a vector4.
  */
  NODISCARD Matrix4
  getInverse() const;

  /**
  * @brief
  *  Creates a 3-dimensional camera matrix.
  * @param at: the look at target of the camera.
  *  eye: the position of the camera.
  *  up: The up vector in the world
  * @return 3 dimensional camera matrix.
  */
  NODISCARD static Matrix4
  lookAt(const Vector3& _at, const Vector3& _eye, const Vector3& _up);

  /**
  * @brief
  *  Creates a 4x4 perspective matrix.
  * @param foV: field of view, aspect: aspect ratio, zNear: near plane location,
  * zFar far plane location.
  * @return Matrix4
  */
  NODISCARD static Matrix4
  perspective(float _foV, float _aspect, float _zNear, float _zFar);

  /**
  * @brief
  *  Create a square matrix with the diagonal component set to _scale.
  * @param scale: vector containing components for scaling.
  * @return Matrix with V along the diagonal, and 1 in the bottom right.
  */
  NODISCARD static Matrix4
  fromScaleVector(const Vector3 _scale); 

  /**
  * @brief
  *  Create a 4x4 matrix from a 3x3 rotation matrix.
  * @param rotation values.
  * @return matrix containing the result.
  */
  NODISCARD static Matrix4
  fromRotationMatrix(float _m00, float _m01, float _m02,
                     float _m10, float _m11, float _m12,
                     float _m20, float _m21, float _m22);
  
  /**
  * @brief
  *  Creates a 4x4 translation matrix from a 3 dimensional vector.
  *  This matrix will have an empty or zero rotation component.
  * @param translation: vector for the translation.
  * @return Matrix containing the result.
  */
  NODISCARD static Matrix4
  fromTranslationVector(const Vector3& _translation);

  /********************************************/
  /*  OPERATORS  */
  /********************************************/

  /**
  * @brief
  *  Multiplies this matrix by another matrix.
  * @param other: matrix to apply the operation with.
  * @return
  *  A reference to this matrix after the multiplication.
  */
  Matrix4&
  operator*=(const Matrix4& other);

  /**
  * @brief
  *  Multiplies this matrix by a given value.
  * @param FLOAT
  * @return
  *  A reference to this matrix after the multiplication.
  */
  Matrix4&
  operator*=(float value);

  /**
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the division.
  */
  NODISCARD Matrix4&
  operator/=(const Matrix4& other);

  /**
  * @brief
  *  Adds another matrix to this matrix
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the addition.
  */
  NODISCARD Matrix4&
  operator+=(const Matrix4& other);

  /**
  * @brief
  *  Subtracts another matrix to this matrix.
  * @param BOWMATRIX&
  * @return
  *  A reference to this matrix after the subtraction.
  */
  NODISCARD Matrix4&
  operator-=(const Matrix4& other);

  /**
  * @brief
  *  Checks if the values between two matrix are different from each other.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix are different in any of its values.
  */
  NODISCARD bool
  operator!=(const Matrix4& other) const;

  /**
  * @brief
  *  Checks if the values between two matrix are the same.
  * @param BOWMATRIX&
  * @return BOOL
  *  Returns true if the matrix have the same values.
  */
  NODISCARD bool
  operator==(const Matrix4& other) const;

  /**
  * @brief
  *  Subtract this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix 
  */
  NODISCARD Matrix4
  operator-(const Matrix4& other) const;

  /**
  * @brief
  *  Adds another matrix to this matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new class with the subtracted values.
  */
  NODISCARD Matrix4
  operator+(const Matrix4& other) const;

  /**
  * @brief
  *  Multiplies this matrix by another matrix.
  * @param BOWMATRIX&
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  Matrix4
  operator*(const Matrix4& other) const;

  /**
  * @brief
  *  Multiplies this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the multiplied values.
  */
  Matrix4
  operator*(float value) const;

  /**
  * @brief
  *  Divides this matrix by another matrix.
  * @param BOWMATRIX
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  Matrix4
  operator/(const Matrix4& other) const;

  /**
  * @brief
  *  Divides this matrix by an scalar.
  * @param FLOAT
  * @return BOWMATRIX
  *  Returns a new matrix with the divided values.
  */
  Matrix4
  operator/(float value) const;

  /**
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
}/// name space bowEngineSDK
