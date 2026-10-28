#pragma once

#include "bowTexture2D.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11Texture2D : public Texture2D
{
 public:

  Dx11Texture2D()
   : texture(nullptr),
    textureView(nullptr)
  {}

  ~Dx11Texture2D() {
    safeRelease(texture);
    safeRelease(textureView);
  }

  /// <summary>
  /// texture member
  /// </summary>
  ID3D11Texture2D* texture;

  /// <summary>
  /// Shader resource view member 
  /// </summary>
  ID3D11ShaderResourceView* textureView;
};
}/// namespace bowEngineSDK
