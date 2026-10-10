#include "bowFigureHelper.h"

#include "bowMath.h"
#include "bowPlane.h"
#include "bowCube.h"
#include "bowSphere.h"
#include "bowVector3.h"

namespace bowEngineSDK
{
bool
FigureHelper::sphereVsSphere(const Sphere& sphere1, const Sphere& sphere2) {
  float dx = sphere1.center.x - sphere2.center.x;
  float dy = sphere1.center.y - sphere2.center.y;
  float dz = sphere1.center.z - sphere2.center.z;
  float dist2 = dx * dx + dy * dy + dz * dz;
  float r = sphere1.radius + sphere2.radius;
  return dist2 <= r * r;
}

bool
FigureHelper::sphereVsPoint(const Sphere& sphere, const Vector3& point) {
  const float dx = sphere.center.x - point.x;
  const float dy = sphere.center.y - point.y;
  const float dz = sphere.center.z - point.z;
  const float dist2 = dx * dx + dy * dy + dz * dz;
  return dist2 <= sphere.radius * sphere.radius;
}

bool
FigureHelper::sphereVsPlane(const Sphere& sphere, const Plane& plane) {
  const float dist = plane.distanceToPoint(sphere.center);
  return Math::abs(dist) <= sphere.radius;
}

bool
FigureHelper::sphereVsAAB(const Sphere& sphere, const AAB& box) {
  const float closeX = Math::clamp(sphere.center.x, box.minPoint.x, box.maxPoint.x);
  const float closeY = Math::clamp(sphere.center.y, box.minPoint.y, box.maxPoint.y);
  const float closeZ = Math::clamp(sphere.center.z, box.minPoint.z, box.maxPoint.z);

  const float dx = sphere.center.x - closeX;
  const float dy = sphere.center.y - closeY;
  const float dz = sphere.center.z - closeZ;

  const float dist2 = dx * dx + dy * dy + dz * dz;
  return dist2 <= sphere.radius * sphere.radius;
}

bool
FigureHelper::planeVsPlane(const Plane& plane1, const Plane& plane2) {
  const Vector3 n1(plane1.x, plane1.y, plane1.z);
  const Vector3 n2(plane2.x, plane2.y, plane2.z);
  const Vector3 direction = n1.cross(n2);
  return direction.sqrMagnitude() > Math::KINDA_SMALL_NUMBER;
}

bool
FigureHelper::planeVsPoint(const Plane& plane, const Vector3& point) {
  return plane.distanceToPoint(point) == 0.0f;
}

bool
FigureHelper::AABVsPlane(const AAB& box, const Plane& plane) {
  const Vector3 center(
    (box.minPoint.x + box.maxPoint.x) * 0.5f,
    (box.minPoint.y + box.maxPoint.y) * 0.5f,
    (box.minPoint.z + box.maxPoint.z) * 0.5f
  );

  const Vector3 extent(
    (box.maxPoint.x - box.minPoint.x) * 0.5f,
    (box.maxPoint.y - box.minPoint.y) * 0.5f,
    (box.maxPoint.z - box.minPoint.z) * 0.5f
  );

  const float distance = plane.distanceToPoint(center);

  const float radius =
    Math::abs(plane.x) * extent.x +
    Math::abs(plane.y) * extent.y +
    Math::abs(plane.z) * extent.z;

  return Math::abs(distance) <= radius;
}

bool FigureHelper::AABVxsAAB(const AAB& box1, const AAB& box2) {
  return
    box1.minPoint.x <= box2.maxPoint.x &&
    box1.maxPoint.x >= box2.minPoint.x &&

    box1.minPoint.y <= box2.maxPoint.y &&
    box1.maxPoint.y >= box2.minPoint.y &&

    box1.minPoint.z <= box2.maxPoint.z &&
    box1.maxPoint.z >= box2.minPoint.z;
}

bool FigureHelper::AAbVspoint(const AAB& box, const Vector3& point) {
  return point.x >= box.minPoint.x && point.x <= box.maxPoint.x &&
    point.y >= box.minPoint.y && point.y <= box.maxPoint.y &&
    point.z >= box.minPoint.z && point.z <= box.maxPoint.z;
}

} // namespace bowEngineSDK
