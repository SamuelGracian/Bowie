#include "bowDx11DepthStencilView.h"

namespace bowEngineSDK {
  
UINT
Dx11DepthStencilView::getClearFlagsDx11(const ClearFlags::E _flags) {
  UINT resultFlag = 0;
  if (hasFlag(_flags, ClearFlags::Depth)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH;
  }

  if (hasFlag(_flags, ClearFlags::Stencil)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL;
  }
  return resultFlag;
}

bool
Dx11DepthStencilView::hasFlag(ClearFlags::E _flag,
                              ClearFlags::E _flagToCheck) {
  return (static_cast<uint8_t> (_flag) & 
          static_cast<uint8_t> (_flagToCheck)) != 0;
}
}/// namespace bowEngineSDK
