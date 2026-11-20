#include "bowDx11DepthStencilView.h"

namespace bowEngineSDK {

Dx11DepthStencilView::~Dx11DepthStencilView() {
  safeRelease(m_depthStencilView);
  safeRelease(m_shadowSRV);
  safeRelease(m_depthTexture);
}

uint32
Dx11DepthStencilView::getClearFlagsDx11(const CLEAR_FLAGS::E flags) {
  uint32 resultFlag = 0;
  if (hasFlag(flags, CLEAR_FLAGS::kDepth)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH;
  }

  if (hasFlag(flags, CLEAR_FLAGS::kStencil)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL;
  }
  return resultFlag;
}

bool
Dx11DepthStencilView::hasFlag(CLEAR_FLAGS::E flag,
                              CLEAR_FLAGS::E flagToCheck) {
  return (static_cast<uint8> (flag) & 
          static_cast<uint8> (flagToCheck)) != 0;
}
}/// name space bowEngineSDK
