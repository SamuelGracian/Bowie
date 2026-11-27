#include "bowCube.h"


namespace bowEngineSDK
{
AAB::AAB(const Vector3& min, const Vector3& max)
  :minPoint(min), maxPoint(max) {}

AAB::AAB(const Vector<Vector3>& points) 
  :minPoint(0.0f,0.0f,0.0f),
   maxPoint(0.0f,0.0f,0.0f)
{
  for (const Vector3& point : points) {
    growthByPoint(point);
  }
}

Vector3
AAB::getCenter() const {
  return Vector3(
    (minPoint.x + maxPoint.x) * 0.5f,
    (minPoint.y + maxPoint.y) * 0.5f,
    (minPoint.z + maxPoint.z) * 0.5f
  );
}

Vector3
AAB::getSize() const {
  return Vector3(
    (maxPoint.x - minPoint.x),
    (maxPoint.y - minPoint.y),
    (maxPoint.z - minPoint.z)
  );
}

void
AAB::moveTo(const Vector3& destiny) {
  const Vector3 centerPoint = getCenter();
  const Vector3 offset(destiny.x - centerPoint.x,
                       destiny.y - centerPoint.y,
                       destiny.z - centerPoint.z);

  minPoint += offset;
  maxPoint += offset;
}

void
AAB::growthByPoint(const Vector3& point) {

    if (point.x < minPoint.x) {
      minPoint.x = point.x;
    }

    if (point.x > maxPoint.x) {
      maxPoint.x = point.x;
    }

    if (point.y < minPoint.y) {
      minPoint.y = point.y;
    }

    if (point.y > maxPoint.y) {
      maxPoint.y = point.y;
    }

    if (point.z < minPoint.z) {
      minPoint.z = point.z;
    }

    if (point.z > maxPoint.z) {
      maxPoint.z = point.z;
    }
}

}/// name space bowEngineSDK
