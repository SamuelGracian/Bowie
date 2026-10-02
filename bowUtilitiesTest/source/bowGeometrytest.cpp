#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "bowPlane.h"

using namespace bowEngineSDK;

TEST_CASE("Geometry tests", "Intersections") {
  SECTION("Plane, constructor, Intersection with another plane") {
    const Vector4 firstVector(10.0f, 5.0f, 6.0f, 0.0f);
    const Vector3 point(10.0f, 5.0f, 6.0f);
    const Vector3 normal(1.0f, 0.0f, 0.0f);

    Plane firstPlane(firstVector);
    Plane secondPlane(point, normal);

    //Point in front of the plane
    REQUIRE(firstPlane.distanceTo(point) == Catch::Approx(161.0f));
    //Point on the plane
    REQUIRE(secondPlane.distance(point) == Catch::Approx(0.0f));
  }
}
