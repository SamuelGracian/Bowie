#include "bowMaterial.h"

namespace bowEngineSDK
{
void
Material::loadTexture(const Map<MATERIAL_TEXTURES::E, String>& texturePack) {
  for (const auto& texturePair : texturePath) {
    SPtr<Texture2D> texture =
      GraphicsAPI::instance().createTexture2DFromFile(texturePair.second);
    if (texture) {
      textures[texturePair.first] = texture;
    }
    else {
      BOW_LOG_ERROR("Failed to load texture" << texturePair.second << std::endl);
    }
  }
}

void
Material::setMaterial() const {
  GraphicsAPI& grapi = GraphicsAPI::instance();
  for (const auto& texturePair : textures) {
    if (!texturePair.second) {
      BOW_LOG_ERROR("Texture not loaded for type" << static_cast<int> (texturePair.first) << std::endl);
      continue;
    }
    grapi.setTexture2D(static_cast<uint32>(texturePair.first), texturePair.second);
  }
}
}