#include "bowCube.h"


namespace bowEngineSDK
{
AAB::AAB(const Vector3& min, const Vector3& max)
  :minPoint(min), maxPoint(max)
  {}

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

  Array<float,24>
  AAB::getCorners() const {
    Array <float, 24> Corners;

  const Vector3 corners[8] = {
  Vector3(minPoint.x, minPoint.y, minPoint.z),
  Vector3(maxPoint.x, minPoint.y, minPoint.z),
  Vector3(minPoint.x, maxPoint.y, minPoint.z),
  Vector3(maxPoint.x, maxPoint.y, minPoint.z),
  Vector3(minPoint.x, minPoint.y, maxPoint.z),
  Vector3(maxPoint.x, minPoint.y, maxPoint.z),
  Vector3(minPoint.x, maxPoint.y, maxPoint.z),
  Vector3(maxPoint.x, maxPoint.y, maxPoint.z)
    };

    for (int i = 0; i < 8; ++i) {
      Corners[i * 3 + 0] = corners[i].x;
      Corners[i * 3 + 1] = corners[i].y;
      Corners[i * 3 + 2] = corners[i].z;
    }

    return Corners;
  }

}

