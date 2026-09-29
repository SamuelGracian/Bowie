#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"

namespace bowEngineSDK
{
bowMatrix::bowMatrix(float M00, float M01, float M02, float M03,
                     float M04, float M05, float M06, float M07,
                     float M08, float M09, float M10, float M11,
                     float M12, float M13, float M14, float M15)
  : matrixV {
  M00, M01, M02, M03,
  M04, M05, M06, M07,
  M08, M09, M10, M11,
  M12, M13, M14, M15
  }{}

bowMatrix::bowMatrix(const std::array<float, 16>& values)
  : matrixV(values){}

void
bowMatrix::setIdentity(){
  for (auto& v : matrixV){ v = 0.0f; }
  matrixV[0] = 1.0f;
  matrixV[5] = 1.0f;
  matrixV[10] = 1.0f;
  matrixV[15] = 1.0f;
}

bowMatrix
bowMatrix::transposed() const{
  bowMatrix result;
  for (int r = 0; r < 4; ++r){
    for (int c = 0; c < 4; ++c){
      result.matrixV[r * 4 + c] = matrixV[c * 4 + r];
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
  const float a00 = matrixV[0], a01 = matrixV[1], a02 = matrixV[2], a03 = matrixV[3];
  const float a10 = matrixV[4], a11 = matrixV[5], a12 = matrixV[6], a13 = matrixV[7];
  const float a20 = matrixV[8], a21 = matrixV[9], a22 = matrixV[10], a23 = matrixV[11];
  const float a30 = matrixV[12], a31 = matrixV[13], a32 = matrixV[14], a33 = matrixV[15];

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
    matrixV[0] * x + matrixV[1] * y + matrixV[2] * z + matrixV[3],
    matrixV[4] * x + matrixV[5] * y + matrixV[6] * z + matrixV[7],
    matrixV[8] * x + matrixV[9] * y + matrixV[10] * z + matrixV[11],
    matrixV[12] * x + matrixV[13] * y + matrixV[14] * z + matrixV[15]
  );
}

Vector4
bowMatrix::transformVector(const Vector3& vector) const{
  const float x = vector.x;
  const float y = vector.y;
  const float z = vector.z;
  return Vector4(
    matrixV[0] * x + matrixV[1] * y + matrixV[2] * z,
    matrixV[4] * x + matrixV[5] * y + matrixV[6] * z,
    matrixV[8] * x + matrixV[9] * y + matrixV[10] * z,
    matrixV[12] * x + matrixV[13] * y + matrixV[14] * z
  );
}

const std::array<float, 16>&
bowMatrix::values()const{
  return matrixV;
}
}