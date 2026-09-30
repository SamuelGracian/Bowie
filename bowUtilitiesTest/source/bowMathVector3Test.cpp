#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

#include "bowVector3.h"
#include "bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Vector3 operations", " [vector 3]") {
  SECTION("Constructors") {
    const Vector3 position { 10.0f, 20.0f, 50.0f };

    position.~Vector3();
  }

  SECTION("Cross product") {
    const Vector3 position { 20.0f, 10.0f, 30.0f };
    const Vector3 position2 { 50.0f, 35.0f, 20.0f };

    const Vector3 crossProduct = position.cross(position2);

    REQUIRE(crossProduct.x == Catch::Approx(-850.0f));
    REQUIRE(crossProduct.y == Catch::Approx(1100.0f));
    REQUIRE(crossProduct.z == Catch::Approx(200.0f));
  }

  SECTION("Dot product") {
    const Vector3 position { 2.0f, 10.0f, 8.0f };
    const Vector3 position2 { 6.0f, 13.0f, 6.0f };

    REQUIRE_THAT (position.dot(position2), Catch::Matchers::WithinRel(190.0f, Math::KINDA_SMALL_NUMBER));
  }

  SECTION("Magnitude and square magnitude") {
    const Vector3 postion { 10.0f, 15.0f, 30.0f };

    REQUIRE(postion.magnitude() == Catch::Approx(35));
    REQUIRE(postion.sqrMagnitude() == Catch::Approx(1225));
  }

  SECTION("Distance") {
    const Vector3 position { 1.0f, 2.0f,6.0f };
    const Vector3 position2 { 4.0f, 6.0f, 8.0f };

    REQUIRE(position.sqrDistance(position2) == Catch::Approx(29.0f));
    REQUIRE_THAT(position.distance(position2), Catch::Matchers::WithinRel( 5.3851f, Math::KINDA_SMALL_NUMBER));
  }

  SECTION("Normalize") {
    const Vector3 position { 3.0f, 4.0f, 6.0f };
    const Vector3 normalized = position.normalize();
    REQUIRE_THAT(normalized.magnitude(), Catch::Matchers::WithinRel(1.0f, Math::KINDA_SMALL_NUMBER));

  }
  SECTION("Vector3 size") {
    REQUIRE(sizeof(Vector3) == sizeof(float) * 3);
  }

  SECTION("Operators", "[Vector3]"){
    Vector3 positionA { 5.0f, 8.0f, 10.0f };
    Vector3 positionB { 6.0f, 9.0f, 5.0f };

    // binary
    REQUIRE((positionA + positionB) == Vector3 { 11.0f, 17.0f, 15.0f });
    REQUIRE((positionB - positionA) == Vector3 { 1.0f, 1.0f, -5.0f });
    REQUIRE((positionA * 2.0f) == Vector3 { 10.0f, 16.0f, 20.0f });
    REQUIRE((positionB / 2.0f) == Vector3 { 3.0f, 4.5f, 2.5f });

    Vector3 temp = positionA;
    temp += positionB;
    REQUIRE(temp == Vector3 { 11.0f, 17.0f, 15.0f });

    temp = positionB;
    temp -= positionA;
    REQUIRE(temp == Vector3 { 1.0f, 1.0f, -5.0f });

    temp = positionA;
    temp *= 2.0f;
    REQUIRE(temp == Vector3 { 10.0f, 16.0f, 20.0f });

    temp = positionB;
    temp /= 2.0f;
    REQUIRE(temp == Vector3 { 3.0f, 4.5f, 2.5f });
  }
}