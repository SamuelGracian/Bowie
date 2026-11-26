#pragma once 

#include "bowCoreRequisites.h"
#include "bowTexture2D.h"
#include "bowGraphicsAPI.h"

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

class BOW_CORE_EXPORT Material
{
public:
  Material() = default;

  void
  loadTexture(const Map<MATERIAL_TEXTURES::E, String>& texturePath);

  void
  setMaterial() const;

 private:
   Map<MATERIAL_TEXTURES::E, SPtr<Texture2D>> textures;
};
}
