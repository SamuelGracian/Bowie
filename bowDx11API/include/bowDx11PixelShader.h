#pragma once

#include "bowPixelShader.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11PixelShader : public PixelShader
{
 public:

   /*
   * @brief
   * Default constructor.
   *  Sets the shader as nullptr
   */
   Dx11PixelShader()
     : pixShader(nullptr)
   {}

   /*
   * @brief
   *  Defualt destructor
   */
   ~Dx11PixelShader() = default;

  /// <summary>
  /// Dx11 Pixel shader
  /// </summary>
  ID3D11PixelShader* pixShader;

};
}/// namespace bowEngineSDK
