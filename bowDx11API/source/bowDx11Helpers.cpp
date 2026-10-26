#include "bowDx11Helpers.h"

namespace bowEngineSDK
{

D3D11_CULL_MODE
Dx11Helpers::getCullMode(CULL_MODE::E _cullMode) const {
  switch (_cullMode) 
  {
  default:
    return D3D11_CULL_MODE::D3D11_CULL_NONE;
    break;

  case CULL_MODE::CULL_BACK:
    return D3D11_CULL_MODE::D3D11_CULL_BACK;
    break;

  case CULL_MODE::CULL_FRONT:
    return D3D11_CULL_MODE::D3D11_CULL_FRONT;
    break;
  }
}

D3D11_FILL_MODE
Dx11Helpers::getFillMode(FILL_MODE::E _fillMode) const {
  switch (_fillMode) {
  default:
    return D3D11_FILL_MODE::D3D11_FILL_SOLID;
    break;

  case FILL_MODE::FILL_WIREFRAME:
    return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    break;
  }
}

/// * or &


}/// namespace bowEngineSDK
