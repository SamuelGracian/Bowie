#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowVector2Int.h"

using namespace bowEngineSDK;

TEST_CASE("Vector 2 int operations", "[Vector2Int]") {
  SECTION("Cosntructors") {
    const Vector2Int position { 1,5 };
    position.~Vector2Int();
  }

  SECTION("Cross product") {
    Vector2Int positionA { 5,8 };
    Vector2Int posiitonB { 10,2 };

    REQUIRE(positionA.cross(posiitonB) == Catch::Approx(-70));
  }

  SECTION("Dot product") {
    Vector2Int positionA { 8,15 };
    Vector2Int posiitonB { 25,6 };

    REQUIRE(positionA.dot(posiitonB) == Catch::Approx(290));
  }

  SECTION("Magnitude and Square magnitude") {
    Vector2Int positionA { 6,8 };
    Vector2Int positionB { 4,5 };
    Vector2Int positionC { 3,8 };

    REQUIRE(positionA.sqrMagnitude() == Catch::Approx(2304));
    REQUIRE(positionA.magnitude() == 48);
    
    REQUIRE(positionB.sqrMagnitude() == 400);
    REQUIRE(positionB.magnitude() == 20);

    REQUIRE(positionC.sqrMagnitude() == 576);
    REQUIRE(positionC.magnitude() == 24);
  }

  SECTION("Distance, Square distance") {
    Vector2Int positionA { 4,15 };
    Vector2Int positionB { 8,6 };

    REQUIRE(positionA.distance(positionB) == 9);
    REQUIRE(positionA.sqrDistance(positionB) == 97);
  }

  SECTION("Operators", "[Vector2]") {
    Vector2Int positionA { 5, 8 };
    Vector2Int positionB { 6, 4 };

    // binary
    REQUIRE((positionA + positionB) == Vector2Int { 11, 12 });
    REQUIRE((positionB - positionA) == Vector2Int { 1, -4 });
    REQUIRE((positionA * 2) == Vector2Int { 10, 16 });
    REQUIRE((positionB / 2) == Vector2Int { 3, 2 });

    Vector2Int temp = positionA;
    temp += positionB;
    REQUIRE(temp == Vector2Int { 11, 12 });

    temp = positionB;
    temp -= positionA;
    REQUIRE(temp == Vector2Int { 1, -4 });

    temp = positionA;
    temp *= 2;
    REQUIRE(temp == Vector2Int { 10, 16 });

    temp = positionB;
    temp /= 2;
    REQUIRE(temp == Vector2Int { 3, 2 });
  }
}