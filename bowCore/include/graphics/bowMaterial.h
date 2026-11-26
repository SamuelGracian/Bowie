#pragma once 

#include "bowCoreRequisites.h"

namespace MATERIAL_TEXTURE
{
enum E
{
  kNormal = 0,
  kAlbedo = 1,
  kSpecular = 2
};
}

namespace bowEngineSDK
{
class Material
{
public:
  Material() = default;

  void
  loadTexture(const Map<MATERIAL_TEXTURE::E, String>& texturePack);

  void
  setMaterial() const;
};
}
