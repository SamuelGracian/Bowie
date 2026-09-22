#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowVector2_int.h"

using namespace bowEngineSDK;

TEST_CASE("Vector 2 int operations", "[Vector2_int]") {
  SECTION("Cosntructors") {
    const Vector2_int position { 1,5 };
    position.~Vector2_int();
  }

  SECTION("Cross product") {
    Vector2_int positionA { 5,8 };
    Vector2_int posiitonB { 10,2 };

    REQUIRE(positionA.cross(posiitonB) == Catch::Approx(-70));
  }

  SECTION("Dot product") {
    Vector2_int positionA { 8,15 };
    Vector2_int posiitonB { 25,6 };

    REQUIRE(positionA.dot(posiitonB) == Catch::Approx(290));
  }

  SECTION("Square magnitude") {
    Vector2_int postionA { 6,18 };

    REQUIRE(postionA.sqrMagitude() == Catch::Approx(11664));
  }

  SECTION("Square distance") {
    Vector2_int positionA { 4,15 };
    Vector2_int positionB { 8,6 };

    REQUIRE(positionA.sqrDistance(positionB) == Catch::Approx(97));
  }

}