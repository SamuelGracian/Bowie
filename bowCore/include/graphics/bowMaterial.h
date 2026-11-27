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
class Texture2D;

class  Material
{
public:
  Material() = default;

  BOW_CORE_EXPORT
  void
  loadTexture(const Map<MATERIAL_TEXTURES::E, String>& texturePath);

  BOW_CORE_EXPORT
  void
  setMaterial() const;

  FORCEINLINE
  void
  setTexture(MATERIAL_TEXTURES::E type, SPtr<Texture2D> texture){
    textures[type] = texture;
  }

 private:
   Map<MATERIAL_TEXTURES::E, SPtr<Texture2D>> textures;
};
}
