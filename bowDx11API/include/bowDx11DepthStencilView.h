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


  static UINT 
  getClearFlagsDx11(const DepthStencilView::ClearFlags _flags);

  static bool
  hasFlag(DepthStencilView::ClearFlags _flag,
          DepthStencilView::ClearFlags _flagToCheck);

  ID3D11DepthStencilView* m_depthStencilView;
  ID3D11ShaderResourceView* m_shadowSRV;
  ID3D11Texture2D* m_depthTexture;
};
}
