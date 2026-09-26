#include "bowMatrix.h"

namespace bowEngineSDK
{

bowMatrix::bowMatrix(float A1, float A2, float A3, float A4,
                     float A5, float A6, float A7, float A8,
                     float A9, float A10, float A11, float A12,
                     float A13, float A14, float A15, float A16)
  : matrixV {
      A1,  A2,  A3,  A4,
      A5,  A6,  A7,  A8,
      A9,  A10, A11, A12,
      A13, A14, A15, A16
  } 
  {}

bowMatrix::bowMatrix(const std::array<float, 16> values)
  : matrixV(values) 
  {}

bowMatrix
bowMatrix::transposed() const {

}

bowMatrix
bowMatrix::identity() const {
  return bowMatrix(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

bowMatrix
bowMatrix::translation(float X, float Y, float Z) const {

}

}