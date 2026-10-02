#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "bowMath.h"
#include "bowMatrix.h"
#include "bowMatrixHelpers.h"
#include "bowVector3.h"
#include "bowVector4.h"

using namespace bowEngineSDK;

namespace
{
void
checkMatrixNear(const Matrix4& actual, const Matrix4& expected) {
  for (int32 row = 0; row < 4; ++row) {
    for (int32 column = 0; column < 4; ++column) {
      CAPTURE(row, column);
      CHECK(actual.data[row][column] ==
            Catch::Approx(expected.data[row][column]).margin(Math::KINDA_SMALL_NUMBER));
    }
  }
}

void
checkVectorNear(const Vector4& actual, float x, float y, float z, float w) {
  CHECK(actual.x == Catch::Approx(x).margin(Math::KINDA_SMALL_NUMBER));
  CHECK(actual.y == Catch::Approx(y).margin(Math::KINDA_SMALL_NUMBER));
  CHECK(actual.z == Catch::Approx(z).margin(Math::KINDA_SMALL_NUMBER));
  CHECK(actual.w == Catch::Approx(w).margin(Math::KINDA_SMALL_NUMBER));
}

// 90 degrees around Z using row vectors (v * M): X goes to Y, Y goes to -X.
const Matrix4 ROTATION_Z_90(0.0f, 1.0f, 0.0f, 0.0f,
                            -1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4 SEQUENCE(1.0f, 2.0f, 3.0f, 4.0f,
                       5.0f, 6.0f, 7.0f, 8.0f,
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);

// The upper 3x3 block has determinant 9, so the inverse has a clean
// closed form: the adjugate divided by 9.
const Matrix4 INVERTIBLE(4.0f, 7.0f, 2.0f, 0.0f,
                         3.0f, 6.0f, 1.0f, 0.0f,
                         2.0f, 5.0f, 3.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4 DIAGONAL(2.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 3.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 4.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 5.0f);
}

TEST_CASE("Matrix operations", " [Matrix 4x4]") {
  SECTION("Constructors") {

    const Matrix4 myMatrix(1, 2, 3, 4,
                           5, 6, 7, 8,
                           9, 10, 11, 12,
                           13, 14, 15, 16);

    for (int i = 0; i < 16; ++i) {
      REQUIRE((&myMatrix.data[0][0])[i] == Catch::Approx(i + 1));
    }
  }
  SECTION("setIdentity produces identity matrix") {
    Matrix4 m;
    m.setIdentity();

    const float* vals = &m.data[0][0];

    for (int i = 0; i < 16; ++i) {
      const int r = i / 4;
      const int c = i % 4;
      if (r == c) {
        REQUIRE(vals[i] == Catch::Approx(1.0f));
      }
    }
  }

  SECTION("Transpose") {

    Matrix4 m(1, 2, 3, 4,
              5, 6, 7, 8,
              9, 10, 11, 12,
              13, 14, 15, 16);

    Matrix4 t = m.transposed();
    const float* mv = &m.data[0][0];
    const float* tv = &t.data[0][0];

    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        REQUIRE(tv[r * 4 + c] == Catch::Approx(mv[c * 4 + r]));
      }
    }
  }

  SECTION("Determinant for a singular matrix is zero") {
    // Rows are linearly dependent so det == 0
    Matrix4 m(1, 2, 3, 4,
              5, 6, 7, 8,
              9, 10, 11, 12,
              13, 14, 15, 16);
    REQUIRE(m.getDeterminant() == Catch::Approx(0.0f));
  }

  SECTION("Inverse of simple diagonal matrix") {
    // Diagonal matrix with non-zero diag
    Matrix4 d(2.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 3.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 4.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 5.0f);

    Matrix4 inv = d.getInverse();
    const float* v = &inv.data[0][0];

    REQUIRE(v[0] == Catch::Approx(1.0f / 2.0f));
    REQUIRE(v[5] == Catch::Approx(1.0f / 3.0f));
    REQUIRE(v[10] == Catch::Approx(1.0f / 4.0f));
    REQUIRE(v[15] == Catch::Approx(1.0f / 5.0f));

    // Off-diagonal remain zero
    for (int i = 0; i < 16; ++i) {
      if (i == 0 || i == 5 || i == 10 || i == 15) continue;
      REQUIRE(v[i] == Catch::Approx(0.0f));
    }
  }

  SECTION("transformPosition vs transformVector (translation)") {
    const float tx = 10.0f, ty = -5.0f, tz = 2.5f;

    Matrix4 t(1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              tx, ty, tz, 1.0f);

    Vector3 p { 1.0f, 2.0f, 3.0f };
    Vector4 pos = t.transformPosition(p);
    Vector4 vec = t.transformVector(p);

    // transformPosition should add translation
    REQUIRE(pos.x == Catch::Approx(1.0f + tx));
    REQUIRE(pos.y == Catch::Approx(2.0f + ty));
    REQUIRE(pos.z == Catch::Approx(3.0f + tz));
    // w component for position should use last column as well
    REQUIRE(pos.w == Catch::Approx(1.0f));

    // transformVector should NOT add translation (w may be 0 or computed without + translate)
    REQUIRE(vec.x == Catch::Approx(1.0f));
    REQUIRE(vec.y == Catch::Approx(2.0f));
    REQUIRE(vec.z == Catch::Approx(3.0f));
  }

  SECTION("Scalar multiplication operator*=") {

    Matrix4 m(1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1);

    auto& saved = (m *= 2.5f);
    (void)saved;
    const float* v = &m.data[0][0];
    REQUIRE(v[0] == Catch::Approx(2.5f));
    REQUIRE(v[5] == Catch::Approx(2.5f));
    REQUIRE(v[10] == Catch::Approx(2.5f));
    REQUIRE(v[15] == Catch::Approx(2.5f));
  }

}

TEST_CASE("Matrix math", "[Matrix]") {
  SECTION("setIdentity overwrites every value") {
    Matrix4 m = SEQUENCE;
    m.setIdentity();

    checkMatrixNear(m, Matrix4::IDENTITY);
  }

  SECTION("Copy constructor and assignment") {
    const Matrix4 copied(SEQUENCE);
    Matrix4 assigned;
    assigned = SEQUENCE;

    checkMatrixNear(copied, SEQUENCE);
    checkMatrixNear(assigned, SEQUENCE);
  }

  SECTION("Equality on const matrices") {
    const Matrix4 same(SEQUENCE);
    Matrix4 different(SEQUENCE);
    different.data[3][3] = 0.0f;

    CHECK(SEQUENCE == same);
    CHECK_FALSE(SEQUENCE != same);
    CHECK(SEQUENCE != different);
    CHECK_FALSE(SEQUENCE == different);
  }

  SECTION("Transposing twice returns the original") {
    checkMatrixNear(SEQUENCE.transposed().transposed(), SEQUENCE);
  }

  SECTION("Addition and subtraction") {
    const Matrix4 doubled = SEQUENCE + SEQUENCE;

    checkMatrixNear(doubled, SEQUENCE * 2.0f);
    checkMatrixNear(doubled - SEQUENCE, SEQUENCE);
    checkMatrixNear(SEQUENCE - SEQUENCE, Matrix4::ZERO);
  }

  SECTION("Compound addition and subtraction") {
    Matrix4 m = SEQUENCE;

    Matrix4& added = (m += SEQUENCE);
    CHECK(&added == &m);
    checkMatrixNear(m, SEQUENCE * 2.0f);

    Matrix4& subtracted = (m -= SEQUENCE);
    CHECK(&subtracted == &m);
    checkMatrixNear(m, SEQUENCE);
  }

  SECTION("Scalar division") {
    const Matrix4 halved = DIAGONAL / 2.0f;

    checkMatrixNear(halved, Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.5f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 2.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 2.5f));
  }

  SECTION("Multiplying by identity returns the same matrix") {
    checkMatrixNear(SEQUENCE * Matrix4::IDENTITY, SEQUENCE);
    checkMatrixNear(Matrix4::IDENTITY * SEQUENCE, SEQUENCE);
  }

  SECTION("Matrix multiplication with known result") {
    checkMatrixNear(SEQUENCE * SEQUENCE, Matrix4(90.0f, 100.0f, 110.0f, 120.0f,
                                                 202.0f, 228.0f, 254.0f, 280.0f,
                                                 314.0f, 356.0f, 398.0f, 440.0f,
                                                 426.0f, 484.0f, 542.0f, 600.0f));
  }

  SECTION("Matrix multiplication is not commutative") {
    const TranslationMatrix translation(Vector3(10.0f, 0.0f, 0.0f));

    CHECK(ROTATION_Z_90 * translation != translation * ROTATION_Z_90);
  }

  SECTION("operator*= matches operator*") {
    Matrix4 m = SEQUENCE;
    m *= INVERTIBLE;

    checkMatrixNear(m, SEQUENCE * INVERTIBLE);
  }

  SECTION("Determinant of known matrices") {
    CHECK(DIAGONAL.getDeterminant() == Catch::Approx(120.0f));
    CHECK(INVERTIBLE.getDeterminant() == Catch::Approx(9.0f));
    CHECK(Matrix4::IDENTITY.getDeterminant() == Catch::Approx(1.0f));
  }

  SECTION("Determinant of the transpose is the same") {
    CHECK(INVERTIBLE.transposed().getDeterminant() == Catch::Approx(9.0f));
  }

  SECTION("Determinant of a product is the product of determinants") {
    CHECK((DIAGONAL * INVERTIBLE).getDeterminant() == Catch::Approx(1080.0f));
  }

  SECTION("Inverse of a dense matrix") {
    const Matrix4 expected(13.0f / 9.0f, -11.0f / 9.0f, -5.0f / 9.0f, 0.0f,
                           -7.0f / 9.0f, 8.0f / 9.0f, 2.0f / 9.0f, 0.0f,
                           3.0f / 9.0f, -6.0f / 9.0f, 3.0f / 9.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f);

    checkMatrixNear(INVERTIBLE.getInverse(), expected);
  }

  SECTION("Matrix times its inverse is identity") {
    checkMatrixNear(INVERTIBLE * INVERTIBLE.getInverse(), Matrix4::IDENTITY);
    checkMatrixNear(INVERTIBLE.getInverse() * INVERTIBLE, Matrix4::IDENTITY);
  }

  SECTION("Matrix division multiplies by the inverse") {
    checkMatrixNear(INVERTIBLE / INVERTIBLE, Matrix4::IDENTITY);

    Matrix4 m = INVERTIBLE;
    Matrix4& divided = (m /= INVERTIBLE);
    CHECK(&divided == &m);
    checkMatrixNear(m, Matrix4::IDENTITY);
  }

  SECTION("Translation matrix") {
    const TranslationMatrix translation(Vector3(10.0f, -5.0f, 2.5f));
    const Vector3 point(1.0f, 2.0f, 3.0f);

    checkVectorNear(translation.transformPosition(point), 11.0f, -3.0f, 5.5f, 1.0f);
    checkVectorNear(translation.transformVector(point), 1.0f, 2.0f, 3.0f, 0.0f);
    CHECK(translation.getDeterminant() == Catch::Approx(1.0f));
  }

  SECTION("Inverse of a translation is the opposite translation") {
    const TranslationMatrix translation(Vector3(10.0f, -5.0f, 2.5f));
    const TranslationMatrix opposite(Vector3(-10.0f, 5.0f, -2.5f));

    checkMatrixNear(translation.getInverse(), opposite);
  }

  SECTION("Rotation with transformPosition") {
    checkVectorNear(ROTATION_Z_90.transformPosition(Vector3(1.0f, 0.0f, 0.0f)),
                    0.0f, 1.0f, 0.0f, 1.0f);
    checkVectorNear(ROTATION_Z_90.transformPosition(Vector3(0.0f, 1.0f, 0.0f)),
                    -1.0f, 0.0f, 0.0f, 1.0f);
    checkVectorNear(ROTATION_Z_90.transformPosition(Vector3(1.0f, 2.0f, 3.0f)),
                    -2.0f, 1.0f, 3.0f, 1.0f);
  }

  SECTION("Rotation with transformVector") {
    checkVectorNear(ROTATION_Z_90.transformVector(Vector3(1.0f, 2.0f, 3.0f)),
                    -2.0f, 1.0f, 3.0f, 0.0f);
  }

  SECTION("Rotate then translate") {
    const TranslationMatrix translation(Vector3(10.0f, -5.0f, 2.5f));
    const Matrix4 rotateThenTranslate = ROTATION_Z_90 * translation;

    checkVectorNear(rotateThenTranslate.transformPosition(Vector3(1.0f, 2.0f, 3.0f)),
                    8.0f, -4.0f, 5.5f, 1.0f);
    checkVectorNear(rotateThenTranslate.transformVector(Vector3(1.0f, 2.0f, 3.0f)),
                    -2.0f, 1.0f, 3.0f, 0.0f);
  }

  SECTION("Translate then rotate") {
    const TranslationMatrix translation(Vector3(10.0f, 0.0f, 0.0f));
    const Matrix4 translateThenRotate = translation * ROTATION_Z_90;

    checkVectorNear(translateThenRotate.transformPosition(Vector3(1.0f, 0.0f, 0.0f)),
                    0.0f, 11.0f, 0.0f, 1.0f);
  }
}
