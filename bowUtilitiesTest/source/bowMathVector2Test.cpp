#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowVector2.h"
#include "bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Vector2 operations", "[Vector2]") {
  SECTION("Constructor and getters") {
    const Vector2 position { 20.0f, 10.0f };

    position.~Vector2();
  }

  SECTION("Cross product") {
    Vector2 position { 20.0f, 10.0f };
    Vector2 position2 { 50.0f, 35.0f };

    // (20 * 35) - (10 * 50) = 200
    REQUIRE(position.cross(position2) == Catch::Approx(200.0f));
    position.~Vector2();
  }

  SECTION("Dot product") {
    Vector2 position { 20.0f, 10.0f };
    Vector2 position2 { 50.0f, 35.0f };

    // (20 * 50) + (10 * 35) = 1350
    REQUIRE(position.dot(position2) == Catch::Approx(1350.0f));
    position.~Vector2();
  }

  SECTION("Magnitude") {
    const Vector2 position { 3.0f, 4.0f };

    REQUIRE(position.sqrMagnitude() == Catch::Approx(25.0f));
    REQUIRE(position.magnitude() == Catch::Approx(5.0f));
    position.~Vector2();
  }

  SECTION("Distance") {
    const Vector2 position { 1.0f, 2.0f };
    const Vector2 position2 { 4.0f, 6.0f };

    REQUIRE(position.sqrDistance(position2) == Catch::Approx(25.0f));
    REQUIRE(position.distance(position2) == Catch::Approx(5.0f));
    position.~Vector2();
  }

  SECTION("Normalize") {
    const Vector2 position { 3.0f, 4.0f };
    const Vector2 normalized = position.normalize();
    REQUIRE_THAT (normalized.magnitude(), Catch::Matchers::WithinRel(1.0f, Math::KINDA_SMALL_NUMBER));
    position.~Vector2();
  }

  SECTION("Vector2 size", "[Vector2]") {
    REQUIRE(sizeof(Vector2) == sizeof(float) * 2);
  }

  SECTION("Operators", "[Vector2]"){
    Vector2 positionA { 5.0f, 8.0f };
    Vector2 positionB { 6.0f, 9.0f };

    // binary
    REQUIRE((positionA + positionB) == Vector2 { 11.0f, 17.0f });
    REQUIRE((positionB - positionA) == Vector2 { 1.0f, 1.0f });
    REQUIRE((positionA * 2.0f) == Vector2 { 10.0f, 16.0f });
    REQUIRE((positionB / 2.0f) == Vector2 { 3.0f, 4.5f });

    Vector2 temp = positionA;
    temp += positionB;
    REQUIRE(temp == Vector2 { 11.0f, 17.0f });

    temp = positionB;
    temp -= positionA;
    REQUIRE(temp == Vector2 { 1.0f, 1.0f });

    temp = positionA;
    temp *= 2.0f;
    REQUIRE(temp == Vector2 { 10.0f, 16.0f });

    temp = positionB;
    temp /= 2.0f;
    REQUIRE(temp == Vector2 { 3.0f, 4.5f });
  }
}