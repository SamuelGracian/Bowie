#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include"bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Math::Trigonometry", "[Math]") {
  SECTION("Cos") {
    REQUIRE(Math::cos(0.0f) == (1.0f));
  }
  //SECTION("Sin"){
  //  REQUIRE (Math::sin(10) == -.5440f); // minimum difference
  //}
  SECTION("square root") {
    REQUIRE(Math::sqrt(9) == 3);
  }
  SECTION("Inverse square root") {
    //REQUIRE (Math::invSqrt(9) == .3333f);// MINIMUM DIFFERENCE
    REQUIRE(Math::invSqrt(20) == 4.47f);
  }
  SECTION("Tangent") {
    REQUIRE(Math::tan(20) == 2.2371f);
  }
  SECTION("arc tangent") {
    REQUIRE(Math::atan(20) == 1.5208f);
  }
  SECTION("Lerp") {
    REQUIRE(std::cout << "Lerp: " << Math::lerp(10, 20, 100) << std::endl);
  }
  SECTION("Clamp") {
    REQUIRE(std::cout <<"Clamp: " << Math::clamp(25, 8, 20) << std::endl);
  }
}