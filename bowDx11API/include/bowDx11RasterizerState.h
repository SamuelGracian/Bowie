/************************************************************************/
/**
 * @file bowDx11ConstBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 * Dx11 implementation for rasterizer state.
 */
 /*************************************************************************/
#pragma once

#include "bowDx11Requisites.h"
#include "bowRasterizerState.h"

namespace bowEngineSDK
{
class Dx11RasterizerState : public RasterizerState
{
  friend class Dx11GraphicsAPI;

 public:
  Dx11RasterizerState ()
    : rasterizer(nullptr),
      rasterizerDesc(nullptr)
  {}
  
  ~Dx11RasterizerState() = default;

  ID3D11RasterizerState* rasterizer;

  const D3D11_RASTERIZER_DESC* rasterizerDesc;
};
}/// name space bowEngineSDK
