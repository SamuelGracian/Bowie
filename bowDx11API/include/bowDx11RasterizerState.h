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
    : rasterizer(nullptr)
  {}
  
  /*
  * @brief
  *  Default destructor.
  */
  FORCEINLINE
  ~Dx11RasterizerState();

  ID3D11RasterizerState* rasterizer;

};

Dx11RasterizerState::~Dx11RasterizerState() {
  rasterizer->Release();
  rasterizer = nullptr;
}

}/// name space bowEngineSDK
