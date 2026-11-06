#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class Topology
{

 public:

  Topology() 
    : m_type (TOPOLOGY_TYPE::TriangleList)
  {}

  virtual ~Topology() = default;

  FORCEINLINE void 
  setType(TOPOLOGY_TYPE::E _type) { m_type = _type; }

  FORCEINLINE TOPOLOGY_TYPE::E
  getType() const { return m_type; }

 protected:
  TOPOLOGY_TYPE::E m_type;

};
}/// namespace bowEngineSDKs
