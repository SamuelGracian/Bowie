#include <catch2/catch_test_macros.hpp>

#include"bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Math::Trigonometry", "[Math]") {
  SECTION("Cos") {
    REQUIRE(Math::cos(0.0f) == 1.0f);
  }
  //SECTION("Sin"){
  //  REQUIRE (Math::sin(10) == -.5440f); // minimum difference
  //}
  SECTION("square root") {
    REQUIRE(Math::sqrt(9) == 3);
  }
  SECTION("Inverse square root") {
    REQUIRE (Math::invSqrt(9) == .3333f);// MINIMUM DIFFERENCE
  }
  SECTION("Tangent") {
    REQUIRE(Math::tan(20) == 2.2371);
  }
}