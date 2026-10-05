#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "bowVector3.h"
#include "bowVector4.h"
#include "bowPlane.h"
#include "bowSphere.h"
#include "bowCube.h"
#include "bowFigureHelper.h"

using namespace bowEngineSDK;

TEST_CASE("Geometry tests", "Intersections") {

  SECTION("Plane: constructors, point and plane intersections") {
    const Vector4 firstVector(10.0f, 5.0f, 6.0f, 0.0f);
    const Vector3 point(10.0f, 5.0f, 6.0f);
    const Vector3 normal(1.0f, 0.0f, 0.0f);

    Plane firstPlane(firstVector);
    Plane secondPlane(point, normal);

    // point on secondPlane
    REQUIRE(FigureHelper::Intersects(secondPlane, point));

    // firstPlane and secondPlane share normal direction.
    // non parallels
    REQUIRE(FigureHelper::Intersects(firstPlane, secondPlane));


    const Vector3 normal2(0.0f, 1.0f, 0.0f);
    const Vector3 pointA(0.0f, 0.0f, 0.0f);
    const Vector3 pointB(0.0f, 5.0f, 0.0f);

    Plane planeA(pointA, normal2);
    Plane planeB(pointB, normal2);

    // Parallel planes
    REQUIRE_FALSE(FigureHelper::Intersects(planeA, planeB));
  }

  SECTION("Plane-plane: non-parallel planes intersect") {
    // two planes with different normals
    Plane p1(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
    Plane p2(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    REQUIRE(FigureHelper::Intersects(p1, p2));
  }

  SECTION("Sphere-sphere intersection") {
    Sphere a(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
    Sphere b(Vector3(1.5f, 0.0f, 0.0f), 1.0f);
    Sphere c(Vector3(3.0f, 0.0f, 0.0f), 0.5f);

    REQUIRE(FigureHelper::Intersects(a, b));
    REQUIRE_FALSE(FigureHelper::Intersects(a, c));

    // t2 spheres touching
    Sphere t(Vector3(2.0f, 0.0f, 0.0f), 1.0f);
    REQUIRE(FigureHelper::Intersects(a, t));
  }

  SECTION("Sphere-point intersection") {
    const Sphere s(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
    const Vector3 inside(0.5f, 0.0f, 0.0f);
    const Vector3 onSurface(1.0f, 0.0f, 0.0f);
    const Vector3 outside(2.0f, 0.0f, 0.0f);

    REQUIRE(FigureHelper::Intersects(s, inside));
    REQUIRE(FigureHelper::Intersects(s, onSurface));
    REQUIRE_FALSE(FigureHelper::Intersects(s, outside));
  }

  SECTION("Sphere-plane intersection") {
    //normal up
    Plane plane(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    Sphere s1(Vector3(0.0f, 0.5f, 0.0f), 1.0f);
    Sphere s2(Vector3(0.0f, 2.0f, 0.0f), 0.4f);

    REQUIRE(FigureHelper::Intersects(s1, plane));
    REQUIRE_FALSE(FigureHelper::Intersects(s2, plane));
  }

  SECTION("Sphere - AAB intersection") {
    //sphere centered at y = 0.5 radius 1->intersects
    AAB box(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));
    Sphere inner(Vector3(0.0f, 0.0f, 0.0f), 0.5f);
    Sphere touching(Vector3(2.0f, 0.0f, 0.0f), 1.0f); 
    Sphere outside(Vector3(3.0f, 0.0f, 0.0f), 0.4f);

    REQUIRE(FigureHelper::Intersects(inner, box));
    REQUIRE(FigureHelper::Intersects(touching, box));
    REQUIRE_FALSE(FigureHelper::Intersects(outside, box));
  }

  SECTION("AAB - plane intersection") {
    Plane plane(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    AAB straddle(Vector3(-1.0f, -0.5f, -1.0f), Vector3(1.0f, 0.5f, 1.0f));
    AAB above(Vector3(-1.0f, 0.1f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

    REQUIRE(FigureHelper::Intersects(straddle, plane));
    REQUIRE_FALSE(FigureHelper::Intersects(above, plane));
  }

  SECTION("AAB - AAB intersection") {
    AAB a(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 2.0f));
    AAB b(Vector3(1.0f, 1.0f, 1.0f), Vector3(3.0f, 3.0f, 3.0f));
    AAB c(Vector3(3.5f, 3.5f, 3.5f), Vector3(4.0f, 4.0f, 4.0f));

    REQUIRE(FigureHelper::Intersects(a, b));
    REQUIRE_FALSE(FigureHelper::Intersects(a, c));
  }

  SECTION("AAB - point intersection") {
    AAB box(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));
    const Vector3 inside(0.0f, 0.0f, 0.0f);
    const Vector3 onEdge(1.0f, 0.0f, 0.0f);
    const Vector3 outside(2.0f, 0.0f, 0.0f);

    REQUIRE(FigureHelper::Intersects(box, inside));
    REQUIRE(FigureHelper::Intersects(box, onEdge));
    REQUIRE_FALSE(FigureHelper::Intersects(box, outside));
  }

}
