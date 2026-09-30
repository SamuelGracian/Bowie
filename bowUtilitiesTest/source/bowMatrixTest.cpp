#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"

using namespace bowEngineSDK;

TEST_CASE("Matrix operations", " [Matrix 4x4]"){
  SECTION("Constructors"){

      const bowMatrix myMatrix(1,2,3,4,
                               5,6,7,8,
                               9,10,11,12,
                               13,14,15,16);

      for (int i = 0; i < 16; ++i){
        REQUIRE((&myMatrix.m_data[0][0])[i] == Catch::Approx(i + 1));
      }
  }
  SECTION("setIdentity produces identity matrix"){
    bowMatrix m;
    m.setIdentity();

    const auto& vals = m.getData();

    for (int i = 0; i < 16; ++i){
      const int r = i / 4;
      const int c = i % 4;
      if (r == c){
        REQUIRE(vals[i] == Catch::Approx(1.0f));
      }
    }
  }

  SECTION("Transpose"){

    bowMatrix m(1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16);

    bowMatrix t = m.transposed();
    const auto& mv = m.getData();
    const auto& tv = t.getData();

    for (int r = 0; r < 4; ++r){
      for (int c = 0; c < 4; ++c){
        REQUIRE(tv[r * 4 + c] == Catch::Approx(mv[c * 4 + r]));
      }
    }
  }

  SECTION("Determinant for a singular matrix is zero"){
    // Rows are linearly dependent so det == 0
    bowMatrix m(1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16);
    REQUIRE(m.getDeterminant() == Catch::Approx(0.0f));
  }

  SECTION("Inverse of simple diagonal matrix"){
    // Diagonal matrix with non-zero diag
    bowMatrix d(2.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 3.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 4.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 5.0f);

    bowMatrix inv = d.getInverse();
    const auto& v = inv.getData();

    REQUIRE(v[0] == Catch::Approx(1.0f / 2.0f));
    REQUIRE(v[5] == Catch::Approx(1.0f / 3.0f));
    REQUIRE(v[10] == Catch::Approx(1.0f / 4.0f));
    REQUIRE(v[15] == Catch::Approx(1.0f / 5.0f));

    // Off-diagonal remain zero
    for (int i = 0; i < 16; ++i){
      if (i == 0 || i == 5 || i == 10 || i == 15) continue;
      REQUIRE(v[i] == Catch::Approx(0.0f));
    }
  }

  SECTION("transformPosition vs transformVector (translation)"){
    const float tx = 10.0f, ty = -5.0f, tz = 2.5f;

    bowMatrix t(1.0f, 0.0f, 0.0f, tx,
                0.0f, 1.0f, 0.0f, ty,
                0.0f, 0.0f, 1.0f, tz,
                0.0f, 0.0f, 0.0f, 1.0f);

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

  SECTION("Scalar multiplication operator*="){

    bowMatrix m(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);

    auto& saved = (m *= 2.5f);
    (void)saved;
    const auto& v = m.getData();
    REQUIRE(v[0] == Catch::Approx(2.5f));
    REQUIRE(v[5] == Catch::Approx(2.5f));
    REQUIRE(v[10] == Catch::Approx(2.5f));
    REQUIRE(v[15] == Catch::Approx(2.5f));
  }

}