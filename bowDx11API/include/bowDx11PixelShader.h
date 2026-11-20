/************************************************************************/
/**
 * @file bowDx11ConstBuffer.h
 * @author Samuel G
 * @date 23/10/2026
 * @brief
 * Dx11 implementation for pixel shader.
 */
 /*************************************************************************/
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
   *  Default destructor
   */
   FORCEINLINE
   ~Dx11PixelShader();

  /// <summary>
  /// Dx11 Pixel shader
  /// </summary>
  ID3D11PixelShader* pixShader;
};

Dx11PixelShader::~Dx11PixelShader() {
  safeRelease(pixShader);
}
}/// name space bowEngineSDK
