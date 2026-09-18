#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Math::Trigonometry", "[Math]") {
  SECTION("Cos") {
    REQUIRE(Math::cos(0.0f) == (1.0f));
    REQUIRE_THAT(Math::cos(50), Catch::Matchers::WithinRel(0.9649f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::cos(25), Catch::Matchers::WithinRel(0.9912f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION ("sin"){
    REQUIRE_THAT(Math::sin(10), Catch::Matchers::WithinRel(-.5440f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::sin(20), Catch::Matchers::WithinRel(0.9129f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::sin(-20), Catch::Matchers::WithinRel(-.9129f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("square root") {
    REQUIRE(Math::sqrt(9) == 3);
    REQUIRE_THAT(Math::sqrt(20), Catch::Matchers::WithinRel(4.4721f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::sqrt(50), Catch::Matchers::WithinRel(7.0710f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Inverse square root") {
    REQUIRE_THAT(Math::invSqrt(20.0f), Catch::Matchers::WithinRel(0.2236f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::invSqrt(150.0f), Catch::Matchers::WithinAbs(0.0816f, Math::KINDA_SMALL_NUMBER));//
    REQUIRE_THAT(Math::invSqrt(1.0f), Catch::Matchers::WithinRel(1.0f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Tangent") {
    REQUIRE_THAT(Math::tan(20), Catch::Matchers::WithinRel(2.2371f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::tan(50), Catch::Matchers::WithinRel(-0.2719f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::tan(62), Catch::Matchers::WithinRel(-1.0975f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("arc tangent") {
    REQUIRE_THAT(Math::atan(20), Catch::Matchers::WithinRel(1.5208f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::atan(80), Catch::Matchers::WithinRel(1.5582f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::atan(120), Catch::Matchers::WithinRel(1.5624f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Arc sin") {
    REQUIRE_THAT(Math::asin(0.80f), Catch::Matchers::WithinAbs(0.9273f, Math::KINDA_SMALL_NUMBER)); //
    REQUIRE_THAT(Math::asin(0.20f), Catch::Matchers::WithinAbs(0.2013f, Math::KINDA_SMALL_NUMBER));
    REQUIRE_THAT(Math::asin(0.35f), Catch::Matchers::WithinAbs(0.3575f, Math::KINDA_SMALL_NUMBER));
    }
  SECTION("Pow") {
    REQUIRE(Math::pow(2, 5) == 32);
    REQUIRE(Math::pow(25, 3) == 15625);
    REQUIRE(Math::pow(8, 6) == 262144);
  }
  SECTION("Lerp") {
    float result = Math::lerp(10, 20, 100);
    INFO("Lerp: " << result);
    REQUIRE_THAT(
      result,
      Catch::Matchers::WithinRel(1010.0f, Math::KINDA_SMALL_NUMBER));
  }
  SECTION("Clamp") {
    float result = Math::clamp(25, 8, 20);
    INFO("Clamp: " << result);
    REQUIRE(result == 20);
  }
  SECTION("PI with atan") {
    float result = 4 * Math::atan(1);
    INFO("Get pi with math functions: " << result);
    REQUIRE_THAT(
      result,
      Catch::Matchers::WithinRel(3.14159265f, Math::KINDA_SMALL_NUMBER));
  }

}