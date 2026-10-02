#include "bowSphere.h"

namespace bowEngineSDK
{
Sphere::Sphere(const Vector3& centerPoint, float _radius)
  :center(centerPoint), radius(_radius)
{}

Sphere::Sphere(float X, float Y, float Z, float _radius)
  :center(X,Y,Z), radius(_radius)
{}

}
