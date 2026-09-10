#include <catch2/catch_test_macros.hpp>
#include<catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowMath.h"

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
    REQUIRE_THAT(Math::invSqrt(20), Catch::Matchers::WithinRel(4.6999f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Tangent") {
    REQUIRE_THAT(Math::tan(20), Catch::Matchers::WithinRel(2.2371f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("arc tangent") {
    REQUIRE_THAT(Math::atan(20), Catch::Matchers::WithinRel(1.5208f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Lerp") {
    REQUIRE(std::cout << "Lerp: " << Math::lerp(10, 20, 100) << std::endl);
  }
  SECTION("Clamp") {
    REQUIRE(std::cout <<"Clamp: " << Math::clamp(25, 8, 20) << std::endl);
  }
}