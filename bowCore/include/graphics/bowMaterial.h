#pragma once 

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
namespace MATERIAL_TEXTURES
{
enum E
{
  kNormal = 0,
  kAlbedo = 1,
  kSpecular = 2
};
}

class Material
{
public:
  Material() = default;

  void
  loadTexture(const Map<MATERIAL_TEXTURES::E, String>& texturePack);

  void
  setMaterial() const;
};
}
