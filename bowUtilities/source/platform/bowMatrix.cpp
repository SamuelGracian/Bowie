#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"

namespace bowEngineSDK
{
bowMatrix::bowMatrix(float M00, float M01, float M02, float M03,
                     float M10, float M11, float M12, float M13,
                     float M20, float M21, float M22, float M23,
                     float M30, float M31, float M32, float M33)
  : m_data {
  M00, M01, M02, M03,
  M10, M11, M12, M13,
  M20, M21, M22, M23,
  M30, M31, M32, M33
  }
{}

void
bowMatrix::setIdentity() {

  m_data[0][0] = 1.0f;
  m_data[1][1] = 1.0f;
  m_data[2][2] = 1.0f;
  m_data[3][3] = 1.0f;
}

bowMatrix
bowMatrix::transposed() const {
  bowMatrix result;
  for (int32 i = 0; i < 4; ++i){
    for (int32 j = 0; j < 4; ++j){
      result.m_data[i][j] = m_data[j][i];
    }
  }
  return result;
}

bowMatrix
bowMatrix::getTransposed() const noexcept {
  return transposed();
}

float
bowMatrix::getDeterminant() const {
  const float a00 = m_data[0][0], a01 = m_data[0][1], a02 = m_data[0][2], a03 = m_data[0][3];
  const float a10 = m_data[1][0], a11 = m_data[1][1], a12 = m_data[1][2], a13 = m_data[1][3];
  const float a20 = m_data[2][0], a21 = m_data[2][1], a22 = m_data[2][2], a23 = m_data[2][3];
  const float a30 = m_data[3][0], a31 = m_data[3][1], a32 = m_data[3][2], a33 = m_data[3][3];

  auto det3 = [](float b00, float b01, float b02,
                 float b10, float b11, float b12,
                 float b20, float b21, float b22) -> float{
                   return b00 * (b11 * b22 - b12 * b21)
                     - b01 * (b10 * b22 - b12 * b20)
                     + b02 * (b10 * b21 - b11 * b20);
    };

  float m0 = det3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
  float m1 = det3(a10, a12, a13, a20, a22, a23, a30, a32, a33);
  float m2 = det3(a10, a11, a13, a20, a21, a23, a30, a31, a33);
  float m3 = det3(a10, a11, a12, a20, a21, a22, a30, a31, a32);

  return a00 * m0 - a01 * m1 + a02 * m2 - a03 * m3;
}

Vector4
bowMatrix::transformPosition(const Vector3& vector) const {
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    m_data[0][0] * x + m_data[0][1] * y + m_data[0][2] * z + m_data[0][3],
    m_data[1][0] * x + m_data[1][1] * y + m_data[1][2] * z + m_data[1][3],
    m_data[2][0] * x + m_data[2][1] * y + m_data[2][2] * z + m_data[2][3],
    m_data[3][0] * x + m_data[3][1] * y + m_data[3][2] * z + m_data[3][3]
  );
}

Vector4
bowMatrix::transformVector(const Vector3& vector) const {
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    m_data[0][0] * x + m_data[0][1] * y + m_data[0][2] * z,
    m_data[1][0] * x + m_data[1][1] * y + m_data[1][2] * z,
    m_data[2][0] * x + m_data[2][1] * y + m_data[2][2] * z,
    m_data[3][0] * x + m_data[3][1] * y + m_data[3][2] * z
  );
}

bowMatrix
bowMatrix::getInverse() const {
  const float* m = &m_data[0][0];
  float inv[16];

  inv[0] = m[5] * m[10] * m[15] -
    m[5] * m[11] * m[14] -
    m[9] * m[6] * m[15] +
    m[9] * m[7] * m[14] +
    m[13] * m[6] * m[11] -
    m[13] * m[7] * m[10];

  inv[1] = -m[1] * m[10] * m[15] +
    m[1] * m[11] * m[14] +
    m[9] * m[2] * m[15] -
    m[9] * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];

  inv[2] = m[1] * m[6] * m[15] -
    m[1] * m[7] * m[14] -
    m[5] * m[2] * m[15] +
    m[5] * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];

  inv[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];

  inv[4] = -m[4] * m[10] * m[15] +
    m[4] * m[11] * m[14] +
    m[8] * m[6] * m[15] -
    m[8] * m[7] * m[14] -
    m[12] * m[6] * m[11] +
    m[12] * m[7] * m[10];

  inv[5] = m[0] * m[10] * m[15] -
    m[0] * m[11] * m[14] -
    m[8] * m[2] * m[15] +
    m[8] * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];

  inv[6] = -m[0] * m[6] * m[15] +
    m[0] * m[7] * m[14] +
    m[4] * m[2] * m[15] -
    m[4] * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];

  inv[8] = m[4] * m[9] * m[15] -
    m[4] * m[11] * m[13] -
    m[8] * m[5] * m[15] +
    m[8] * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];

  inv[9] = -m[0] * m[9] * m[15] +
    m[0] * m[11] * m[13] +
    m[8] * m[1] * m[15] -
    m[8] * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];

  inv[10] = m[0] * m[5] * m[15] -
    m[0] * m[7] * m[13] -
    m[4] * m[1] * m[15] +
    m[4] * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];

  inv[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];

  inv[12] = -m[4] * m[9] * m[14] +
    m[4] * m[10] * m[13] +
    m[8] * m[5] * m[14] -
    m[8] * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];

  inv[13] = m[0] * m[9] * m[14] -
    m[0] * m[10] * m[13] -
    m[8] * m[1] * m[14] +
    m[8] * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];

  inv[14] = -m[0] * m[5] * m[14] +
    m[0] * m[6] * m[13] +
    m[4] * m[1] * m[14] -
    m[4] * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];

  inv[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];

  float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (0.0F == det){
    // Non-invertible: return zero-initialized matrix
    return bowMatrix();
  }

  float invDet = 1.0f / det;
  bowMatrix result;
  for (int32 i = 0; i < 16; ++i){
    (&result.m_data[0][0])[i] = inv[i] * invDet;
  }

  return result;
}

const float *
bowMatrix::getData() const noexcept {
  return &m_data[0][0];
}

FORCELINE bowMatrix&
bowMatrix::operator*= (const bowMatrix& other) {
  bowMatrix result;

  for (size_t row = 0; row < 4; ++row){
    for (size_t column = 0; column < 4; ++column){
      result.m_data[row][column] = 0.0f;

      for (size_t k = 0; k < 4; ++k){
        result.m_data[row][column] += m_data[row][k] * other.m_data[k][column];
      }
    }
  }

 return *this = result;
}

FORCELINE bowMatrix&
bowMatrix::operator*= (float value) {
  float* data = &m_data[0][0];

  for (int32 i = 0; i < 16; i++){
    data[i] *= value;
  }
  return *this;
}

FORCELINE bowMatrix
bowMatrix::operator*(const bowMatrix& other) const {
  bowMatrix result;
  for (int32 row = 0; row < 4; row++){
    for (int32 column = 0; column < 4; ++column){
      result.m_data[row][column] = 0.0f;

      for (int32 k = 0; k < 4; ++k){
        result.m_data[row][column] += m_data[row][column] * other.m_data[row][column];
      }
    }
  }

  return result;
}

FORCELINE bowMatrix&
bowMatrix::operator/= (const bowMatrix& other) {
  *this = (*this) * other.getInverse();
  return *this;
}

FORCELINE bowMatrix&
bowMatrix::operator+=(const bowMatrix& other){
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      m_data[row][column] += other.m_data[row][column];
    }
  }

  return *this;
}

FORCELINE bowMatrix&
bowMatrix::operator-= (const bowMatrix& other) {
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      m_data[row][column] -= other.m_data[row][column];
    }
  }

  return *this;
}

FORCELINE bool
bowMatrix::operator!=(const bowMatrix& other) {
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      if (m_data[row][column] != other.m_data[row][column]){
        return true;
      }
    }
  }
  return false;
}

FORCELINE bool
bowMatrix::operator==(const bowMatrix& other) {
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      if (m_data[row][column] != other.m_data[row][column]){
        return false;
      }
    }
  }

  return true;
}

FORCELINE bowMatrix
bowMatrix::operator-(const bowMatrix& other) const {
  bowMatrix result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.m_data[row][column] = m_data[row][column] - other.m_data[row][column];
    }
  }

  return result;
}

FORCELINE bowMatrix
bowMatrix::operator+(const bowMatrix& other) const {
  bowMatrix result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.m_data[row][column] = m_data[row][column] + other.m_data[row][column];
    }
  }

  return result;
}

FORCELINE bowMatrix
bowMatrix::operator* (float value) const {
  bowMatrix result = *this;
  float* data = &result.m_data[0][0];
  for (int32 i = 0; i < 16; ++i){
    data[i] *= value;
  }

  return result;
}

FORCELINE bowMatrix
bowMatrix::operator/(const bowMatrix& other) const {
  bowMatrix result;
  result = (*this) * other.getInverse();
  return result;
}

FORCELINE bowMatrix
bowMatrix::operator/(float scalar) const {
  bowMatrix result = *this;
  float* data = &result.m_data[0][0];
  for (int32 i = 0; i < 16; ++i){
    data[i] /= scalar;
  }

  return result;
}

} // namespace bowEngineSDK