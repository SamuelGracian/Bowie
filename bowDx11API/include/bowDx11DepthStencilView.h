#pragma once

#include "bowDepthStencilView.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11DepthStencilView : public DepthStencilView
{
 public:
  Dx11DepthStencilView()
   : m_depthStencilView(nullptr),
     m_shadowSRV(nullptr),
     m_depthTexture(nullptr)
  {}
 
  ~Dx11DepthStencilView() = default;

  static uint32
  getClearFlagsDx11(const CLEAR_FLAGS::E _flags);

  static bool
  hasFlag(CLEAR_FLAGS::E _flag,
          CLEAR_FLAGS::E _flagToCheck);

  ID3D11DepthStencilView* m_depthStencilView;
  ID3D11ShaderResourceView* m_shadowSRV;
  ID3D11Texture2D* m_depthTexture;
};
}
