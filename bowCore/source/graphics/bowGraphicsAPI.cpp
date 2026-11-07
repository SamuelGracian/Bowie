#include "bowGraphicsAPI.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace bowEngineSDK
{
namespace ImageLoader
{
Vector<uint8>
loadImageFromFile(const String& filePath, int32* outWidth, int32* outHeight,
                                           int32* outChanels) {

  Vector<uint8_t> imageData;

  uint8* data = stbi_load(filePath.c_str(),
                          outWidth, outHeight, outChanels, STBI_rgb_alpha);

  if (data) {
    imageData.resize((*outWidth) * (*outHeight) * STBI_rgb_alpha);
    memcpy(imageData.data(), data, imageData.size());
    stbi_image_free(data);
  }
  else {
    std::cout << "Error loading image: " << filePath << std::endl;
  }

  return imageData;
}
}/// namespace imageLoader

GraphicsAPI::~GraphicsAPI() {}

SPtr<Texture2D>
GraphicsAPI::createTexture2DFromFile(const String& _filePath) {

  int32 width = 0;
  int32 height = 0;
  int32 channels = 0;

  Vector<uint8> imgData = ImageLoader::loadImageFromFile(_filePath, &width,
                                                         &height, &channels);
  if (imgData.empty()) {
    return nullptr;
  }

  return createTexture2DWithImageData(imgData, width, height);
}

}/// namespace bowEngneSDK
