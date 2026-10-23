#include "bowDx11Topology.h"

namespace bowEngineSDK
{
Dx11Topology::Dx11Topology()
  : dx11Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {
  switch (m_type) {

  case Topology::Type::TriangleList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;

  case Topology::Type::TriangleStrip:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    break;

  case Topology::Type::LineList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    break;

  case Topology::Type::PointList:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    break;

  default:
    dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;
  }
}
}/// namespace bowEngineSDK
