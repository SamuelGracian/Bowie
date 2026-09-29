#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"

namespace bowEngineSDK
{
bowMatrix::bowMatrix(float M00, float M01, float M02, float M03,
                     float M04, float M05, float M06, float M07,
                     float M08, float M09, float M10, float M11,
                     float M12, float M13, float M14, float M15)
  : m_data {
  M00, M01, M02, M03,
  M04, M05, M06, M07,
  M08, M09, M10, M11,
  M12, M13, M14, M15
  }{}

bowMatrix::bowMatrix(const std::array<float, 16>& values)
  : m_data(values){}

void
bowMatrix::setIdentity(){
  for (auto& v : m_data){ v = 0.0f; }
  m_data[0] = 1.0f;
  m_data[5] = 1.0f;
  m_data[10] = 1.0f;
  m_data[15] = 1.0f;
}

bowMatrix
bowMatrix::transposed() const{
  bowMatrix result;
  for (int r = 0; r < 4; ++r){
    for (int c = 0; c < 4; ++c){
      result.m_data[r * 4 + c] = m_data[c * 4 + r];
    }
  }
  return result;
}

bowMatrix
bowMatrix::getTransposed() const noexcept{
  return transposed();
}

float
bowMatrix::getDeterminant() const{
  const float a00 = m_data[0], a01 = m_data[1], a02 = m_data[2], a03 = m_data[3];
  const float a10 = m_data[4], a11 = m_data[5], a12 = m_data[6], a13 = m_data[7];
  const float a20 = m_data[8], a21 = m_data[9], a22 = m_data[10], a23 = m_data[11];
  const float a30 = m_data[12], a31 = m_data[13], a32 = m_data[14], a33 = m_data[15];

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
bowMatrix::transformPosition(const Vector3& vector) const{
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    m_data[0] * x + m_data[1] * y + m_data[2] * z + m_data[3],
    m_data[4] * x + m_data[5] * y + m_data[6] * z + m_data[7],
    m_data[8] * x + m_data[9] * y + m_data[10] * z + m_data[11],
    m_data[12] * x + m_data[13] * y + m_data[14] * z + m_data[15]
  );
}

Vector4
bowMatrix::transformVector(const Vector3& vector) const{
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    m_data[0] * x + m_data[1] * y + m_data[2] * z,
    m_data[4] * x + m_data[5] * y + m_data[6] * z,
    m_data[8] * x + m_data[9] * y + m_data[10] * z,
    m_data[12] * x + m_data[13] * y + m_data[14] * z
  );
}

bowMatrix
bowMatrix::getInverse() const{
  const float* m = m_data.data();
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

  if (det == 0.0f){
    // Non-invertible: return zero-initialized matrix
    return bowMatrix();
  }

  float invDet = 1.0f / det;
  std::array<float, 16> out;
  for (int i = 0; i < 16; ++i){
    out[i] = inv[i] * invDet;
  }

  return bowMatrix(out);
}

const std::array<float, 16>&
bowMatrix::values() const noexcept{
  return m_data;
}

FORCELINE bowMatrix&
bowMatrix::operator*= (const bowMatrix& other){
  bowMatrix result;

  for (int row = 0; row < 4; ++row){
    for (int column = 0; column < 4; ++column){
      float value = 0.0f;

      for (int k = 0; k < 4; ++k){
        value += m_data[row * 4 + k]
          * other.m_data[k * 4 + column];
      }
      result.m_data[row * 4 + column] = value;
    }
  }
  // assign computed result back to this
  m_data = result.m_data;
  return *this;
}
FORCELINE bowMatrix&
bowMatrix::operator*= (float value){
  for (size_t i = 0; i < m_data.size(); ++i){
    m_data[i] = m_data[i] * value;
  }
  return *this;
}

FORCELINE bowMatrix
bowMatrix::operator*(const bowMatrix& other) const{
  bowMatrix result;
  for (int row = 0; row < 4; ++row){
    for (int column = 0; column < 4; ++column){
      float value = 0.0f;

      for (int k = 0; k < 4; ++k){
        value += m_data[row * 4 + k]
          * other.m_data[k * 4 + column];
      }

      result.m_data[row * 4 + column] = value;
    }
  }

  return result;
}

FORCELINE bowMatrix&
bowMatrix::operator/= (const bowMatrix& other){
  *this = (*this) * other.getInverse();
  return *this;
}


FORCELINE bowMatrix&
bowMatrix::operator+=(const bowMatrix& other){
  for (size_t i = 0; i < other.m_data.size(); ++i){
    m_data[i] += other.m_data[i];
  }
  return *this;
}

FORCELINE bowMatrix&
bowMatrix::operator-= (const bowMatrix& other){
  for (size_t i = 0; i < other.m_data.size(); ++i){
    m_data[i] -= other.m_data[i];
  }
  return *this;
}

FORCELINE bool
bowMatrix::operator!=(const bowMatrix& other){
  for (size_t i = 0; i < other.m_data.size(); ++i){
    if (m_data[i] != other.m_data[i]){
      return false;
    }
  }
  return true;
}

FORCELINE bool
bowMatrix::operator==(const bowMatrix& other){
  for (size_t i = 0; i < other.m_data.size(); ++i){
    if (m_data[i] == other.m_data[i]){
      return true;
    }
  }
  return false;
}

FORCELINE bowMatrix
bowMatrix::operator-(const bowMatrix& other) const{
  bowMatrix result;
  for (size_t i = 0; i < other.m_data.size(); ++i){
    result.m_data[i] = m_data[i] - other.m_data[i];
  }
  return result;
}

FORCELINE bowMatrix
bowMatrix::operator+(const bowMatrix& other) const{
  bowMatrix result;
  for (size_t i = 0; i < other.m_data.size(); ++i){
    result.m_data[i] = m_data[i] + other.m_data[i];
  }
  return result;
}

FORCELINE bowMatrix
bowMatrix::operator* (float value) const{
  bowMatrix result;
  for (size_t i = 0; i < m_data.size(); ++i){
    result.m_data[i] = m_data[i] * value;
  }
  return result;
}

FORCELINE bowMatrix
bowMatrix::operator/(const bowMatrix& other) const{
  bowMatrix result;
  result = (*this) * other.getInverse();
  return result;
}

FORCELINE bowMatrix
bowMatrix::operator/(float scalar) const{
  bowMatrix result;
  for (size_t i = 0; i < m_data.size(); ++i){
    result.m_data[i] = m_data[i] / scalar;
  }
  return result;
}

} // namespace bowEngineSDK