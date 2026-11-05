#include "bowDx11Topology.h"

namespace bowEngineSDK
{
Dx11Topology::Dx11Topology()
  : dx11Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {
  switch (m_type) {

  case TOPOLOGY_TYPE::TriangleList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;

  case TOPOLOGY_TYPE::TriangleStrip:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    break;

  case TOPOLOGY_TYPE::LineList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    break;

  case TOPOLOGY_TYPE::PointList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    break;

  default:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;
  }
}
}/// namespace bowEngineSDK
