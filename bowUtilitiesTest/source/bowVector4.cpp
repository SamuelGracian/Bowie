#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "bowVector4.h"

using namespace bowEngineSDK;

TEST_CASE("Vector4 constructors", "[Vector4]") {
  SECTION("Constructor from components") {
    const Vector4 vector(1.0f, 2.0f, 3.0f, 4.0f);

    REQUIRE(vector.x == Catch::Approx(1.0f));
    REQUIRE(vector.y == Catch::Approx(2.0f));
    REQUIRE(vector.z == Catch::Approx(3.0f));
    REQUIRE(vector.w == Catch::Approx(4.0f));
  }
}

TEST_CASE("Vector4 dot product") {
  const Vector4 first(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4 second(5.0f, 6.0f, 7.0f, 8.0f);

  REQUIRE(first.dot(second) == Catch::Approx(70.0f));
}

TEST_CASE("Vector4 cross product") {
  const Vector4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
  const Vector4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);

  const Vector4 result = xAxis.cross(yAxis);

  REQUIRE(result.x == Catch::Approx(0.0f));
  REQUIRE(result.y == Catch::Approx(0.0f));
  REQUIRE(result.z == Catch::Approx(1.0f));
  REQUIRE(result.w == Catch::Approx(0.0f));
}

TEST_CASE("Vector4 magnitude") {
  const Vector4 vector(1.0f, 2.0f, 2.0f, 0.0f);

  REQUIRE(vector.sqrMagnitude() == Catch::Approx(9.0f));
  REQUIRE(vector.magnitude() == Catch::Approx(3.0f));
}

TEST_CASE("Vector4 squared distance") {
  const Vector4 first(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4 second(2.0f, 4.0f, 6.0f, 8.0f);

  REQUIRE(first.sqrDistance(second) == Catch::Approx(30.0f));
}

TEST_CASE("Vector4 distance") {
  const Vector4 first(0.0f, 0.0f, 0.0f, 0.0f);
  const Vector4 second(1.0f, 2.0f, 2.0f, 0.0f);

  REQUIRE(first.distance(second) == Catch::Approx(3.0f));
}

TEST_CASE("Vector4 normalize") {
  const Vector4 vector(1.0f, 2.0f, 2.0f, 0.0f);

  const Vector4 normalized = vector.normalize();

  REQUIRE(normalized.x == Catch::Approx(1.0f / 3.0f));
  REQUIRE(normalized.y == Catch::Approx(2.0f / 3.0f));
  REQUIRE(normalized.z == Catch::Approx(2.0f / 3.0f));
  REQUIRE(normalized.w == Catch::Approx(0.0f));
  REQUIRE(normalized.magnitude() == Catch::Approx(1.0f));
}