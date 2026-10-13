#include "bowCore.h"

namespace bowEngineSDK
{
Vector3 bowCoreAddiiton(const Vector3 a, const Vector3 b) {
  Vector3 r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  r.z = a.z + b.z;
  return r;
}
}
