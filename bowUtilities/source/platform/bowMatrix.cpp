/************************************************************************/
/**
 * @file bowMatrix.cpp
 * @author Samuel G
 * @date 24/09/2026
 *
 */
 /************************************************************************/

#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"

namespace bowEngineSDK
{

const Matrix4 
Matrix4::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4
Matrix4::ZERO(0.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 0.0f);


Matrix4::Matrix4(float M00, float M01, float M02, float M03,
                 float M10, float M11, float M12, float M13,
                 float M20, float M21, float M22, float M23,
                 float M30, float M31, float M32, float M33)
  : data {
  M00, M01, M02, M03,
  M10, M11, M12, M13,
  M20, M21, M22, M23,
  M30, M31, M32, M33
  }{}

Matrix4::Matrix4(const Matrix4& copy){
  for (int32 i = 0; i < 4; ++i){
    for (int32 j = 0; j < 4; ++j){
      data[i][j] = copy.data[i][j];
    }
  }
}

void
Matrix4::setIdentity(){
  *this = IDENTITY;
}

Matrix4
Matrix4::transposed() const{
  Matrix4 result;
  for (int32 i = 0; i < 4; ++i){
    for (int32 j = 0; j < 4; ++j){
      result.data[i][j] = data[j][i];
    }
  }
  return result;
}

float
Matrix4::getDeterminant() const{
  const float a00 = data[0][0];
  const float a01 = data[0][1];
  const float a02 = data[0][2];
  const float a03 = data[0][3];

  const float a10 = data[1][0];
  const float a11 = data[1][1];
  const float a12 = data[1][2];
  const float a13 = data[1][3];

  const float a20 = data[2][0];
  const float a21 = data[2][1];
  const float a22 = data[2][2];
  const float a23 = data[2][3];

  const float a30 = data[3][0];
  const float a31 = data[3][1];
  const float a32 = data[3][2];
  const float a33 = data[3][3];

  auto det3 = [](float b00, float b01, float b02,
                 float b10, float b11, float b12,
                 float b20, float b21, float b22) -> float{
                   return b00 * (b11 * b22 - b12 * b21)
                     - b01 * (b10 * b22 - b12 * b20)
                     + b02 * (b10 * b21 - b11 * b20);
    };

  const float m0 = det3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
  const float m1 = det3(a10, a12, a13, a20, a22, a23, a30, a32, a33);
  const float m2 = det3(a10, a11, a13, a20, a21, a23, a30, a31, a33);
  const float m3 = det3(a10, a11, a12, a20, a21, a22, a30, a31, a32);

  return a00 * m0 - a01 * m1 + a02 * m2 - a03 * m3;
}

Vector4
Matrix4::transformPosition(const Vector3& vector) const{
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;

  return Vector4(
    data[0][0] * x + data[0][1] * y + data[0][2] * z + data[3][0],
    data[1][0] * x + data[1][1] * y + data[1][2] * z + data[3][1],
    data[2][0] * x + data[2][1] * y + data[2][2] * z + data[3][2],
    data[3][3]
  );
}

Vector4
Matrix4::transformVector(const Vector3& vector) const{
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    data[0][0] * x + data[0][1] * y + data[0][2] * z,
    data[1][0] * x + data[1][1] * y + data[1][2] * z,
    data[2][0] * x + data[2][1] * y + data[2][2] * z,
    data[3][0] * x + data[3][1] * y + data[3][2] * z
  );
}

Matrix4
Matrix4::getInverse() const{
  const float* m = &data[0][0];
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

  const float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (0.0f == det){
    // Non-invertible: return zero-initialized matrix
    return Matrix4();
  }

  const float invDet = 1.0f / det;
  Matrix4 result;
  int32 idx = 0;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = inv[idx++] * invDet;
    }
  }

  return result;
}

/*     OPERATORS     */

Matrix4&
Matrix4::operator*=(const Matrix4& other){
  float result[4][4] {};

  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      for (int32 k = 0; k < 4; ++k){
        result[row][column] += data[row][k] * other.data[k][column];
      }
    }
  }

  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      data[row][column] = result[row][column];
    }
  }

  return *this;
}

Matrix4&
Matrix4::operator*=(float value){
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      data[row][column] *= value;
    }
  }

  return *this;
}

Matrix4&
Matrix4::operator/=(const Matrix4& other){
  *this = (*this) * other.getInverse();

  return *this;
}

Matrix4&
Matrix4::operator+=(const Matrix4& other){
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      data[row][column] += other.data[row][column];
    }
  }

  return *this;
}

Matrix4&
Matrix4::operator-=(const Matrix4& other){
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      data[row][column] -= other.data[row][column];
    }
  }

  return *this;
}

bool
Matrix4::operator!=(const Matrix4& other) const{
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      if (data[row][column] != other.data[row][column]){
        return true;
      }
    }
  }

  return false;
}

bool
Matrix4::operator==(const Matrix4& other) const{
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      if (data[row][column] != other.data[row][column]){
        return false;
      }
    }
  }

  return true;
}

Matrix4
Matrix4::operator*(float value) const{
  Matrix4 result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = data[row][column] * value;
    }
  }

  return result;
}

Matrix4
Matrix4::operator*(const Matrix4& other) const{
  Matrix4 result;
  for (int32 row = 0; row < 4; row++){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = 0.0f;

      for (int32 k = 0; k < 4; ++k){
        result.data[row][column] += data[row][column] * other.data[row][column];
      }
    }
  }

  return result;
}

Matrix4
Matrix4::operator-(const Matrix4& other) const{
  Matrix4 result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = data[row][column] - other.data[row][column];
    }
  }

  return result;
}

Matrix4
Matrix4::operator+(const Matrix4& other) const{
  Matrix4 result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = data[row][column] + other.data[row][column];
    }
  }

  return result;
}


Matrix4
Matrix4::operator/(const Matrix4& other) const{
  Matrix4 result;
  result = (*this) * other.getInverse();

  return result;
}

Matrix4
Matrix4::operator/(float scalar) const{
  Matrix4 result;
  for (int32 row = 0; row < 4; ++row){
    for (int32 column = 0; column < 4; ++column){
      result.data[row][column] = data[row][column] / scalar;
    }
  }

  return result;
}
} // namespace bowEngineSDK
