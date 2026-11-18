#pragma once 

#include "bowDx11Requisites.h"
#include "bowTopology.h"

namespace bowEngineSDK
{
class Dx11Topology : public Topology
{
  friend class Dx11GraphicsAPI;

 public:
  Dx11Topology();

  ~Dx11Topology() = default;

  FORCEINLINE D3D11_PRIMITIVE_TOPOLOGY
  getDx11Topology() { return dx11Topology; }

 protected:

  /**
  * @brief
  *  Dx11 topology object.
  */
  D3D11_PRIMITIVE_TOPOLOGY dx11Topology;

};
}/// name space bowEngineSDK
