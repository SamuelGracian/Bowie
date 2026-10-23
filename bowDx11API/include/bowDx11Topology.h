#pragma once 

#include "bowDx11Requisites.h"
#include "bowTopology.h"


namespace bowEngineSDK
{
class Dx11Topology : public Topology
{

 public:
  Dx11Topology();

  ~Dx11Topology() = default;

  FORCEINLINE D3D11_PRIMITIVE_TOPOLOGY
  getDx11Topology() { return dx11Topology; }

   /// <summary>
   /// Topology member
   /// </summary>
   D3D11_PRIMITIVE_TOPOLOGY dx11Topology;

};
}/// namespace bowEngineSDK
