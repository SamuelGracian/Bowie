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
  /**
  * @brief
  *  Default constructor.
  */
  Material() = default;

  /**
  * @brief
  *  Gets the file path for the texture creating its own object, and saving it
  *  in the textures map
  * @param texturePath: map with the material texture and its file path.
  * @return none.
  */
  BOW_CORE_EXPORT
  void
  loadTexture(const Map<MATERIAL_TEXTURES::E, String>& texturePath);

  /*
  * @brief
  *  Calling graphics API sets the texture depending its order on the map.
  * @param none.
  * @return none.
  */
  BOW_CORE_EXPORT
  void
  setMaterial() const;

  /**
  * @brief
  *  Saves a texture and its type in the textures map.
  * @param type: Type of the texture ( read MATERIAL_TEXTURES, for more context)
  * @parma texture: Share pointer to a texture object.
  * @return none.
  */
  FORCEINLINE
  void
  setTexture(MATERIAL_TEXTURES::E type, SPtr<Texture2D> texture){
    textures[type] = texture;
  }

  /**
  * @brief
  *  Checks if the textures map is empty.
  * @param none
  * @return: If the map isn't empty returns true as a valid material.
  */
  bool
  isValid() const;

 private:
   Map<MATERIAL_TEXTURES::E, SPtr<Texture2D>> textures;
};
}
