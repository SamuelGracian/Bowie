#include "bowDx11Topology.h"

namespace bowEngineSDK
{
Dx11Topology::Dx11Topology()
  : dx11Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {
  switch (m_type) {

  case TOPOLOGY_TYPE::kTriangleList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;

  case TOPOLOGY_TYPE::kTriangleStrip:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    break;

  case TOPOLOGY_TYPE::kLineList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    break;

  case TOPOLOGY_TYPE::kPointList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    break;

  default:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;
  }
}
}/// name space bowEngineSDK
