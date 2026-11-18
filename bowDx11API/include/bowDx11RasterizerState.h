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
  
  ~Dx11RasterizerState();

  ID3D11RasterizerState* rasterizer;

  const D3D11_RASTERIZER_DESC* rasterizerDesc;
};

Dx11RasterizerState::~Dx11RasterizerState() {
  rasterizer = nullptr;
  rasterizerDesc = nullptr;
}

}/// name space bowEngineSDK
