#pragma once

#include "bowDx11Requisites.h"
#include "bowRasterizerState.h"

namespace bowEngineSDK
{
class Dx11RasterizerState : public RasterizerState
{
 public:
  Dx11RasterizerState ()
    : rasterizer(nullptr),
      rasterizerDesc(nullptr)
  {}
  
  ~Dx11RasterizerState() {
    safeRelease(rasterizer);
    safeRelease(rasterizerDesc);
  }

  /// <summary>
  /// rasterizer state member
  /// </summary>
  ID3D11RasterizerState* rasterizer;
  /// <summary>
  /// Rasterizer state descriptor.
  /// </summary>
  const D3D11_RASTERIZER_DESC* rasterizerDesc;
};
}/// namespace bowEngineSDK
