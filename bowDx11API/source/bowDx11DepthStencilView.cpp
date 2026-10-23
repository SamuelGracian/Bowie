#include "bowDx11DepthStencilView.h"

namespace bowEngineSDK {
  
UINT
Dx11DepthStencilView::getClearFlagsDx11(const DepthStencilView::ClearFlags _flags) {
  UINT resultFlag = 0;
  if (hasFlag(_flags, DepthStencilView::ClearFlags::Depth)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH;
  }

  if (hasFlag(flag, DepthStencilView::ClearFlags::Stencil)) {
    resultFlag |= D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL;
  }
  return resultFlag;

}

bool
Dx11DepthStencilView::hasFlag(DepthStencilView::ClearFlags _flag,
                              DepthStencilView::ClearFlags _flagToCheck) {

  return (static_cast<uint8_t> (_flag) & 
          static_cast<uint8_t> (_flagToCheck)) != 0;
}


}/// namespace bowEngineSDK

