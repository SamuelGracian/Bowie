#include "bowDx11DepthStencilView.h"

namespace bowEngineSDK {
  
UINT
Dx11DepthStencilView::getClearFlagsDx11(const CLEAR_FLAGS::E flags) {
  UINT resultFlag = 0;
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
