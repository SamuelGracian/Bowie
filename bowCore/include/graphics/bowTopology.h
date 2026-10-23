#pragma once


#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class Topology
{
 public:
  enum Type : uint32
  {
    TriangleList = 0,
    TriangleStrip,
    LineList,
    PointList
  };

 public:

  Topology() 
    : m_type (Type::TriangleList)
  {}

  virtual ~Topology() = default;

  FORCEINLINE void 
  setType(Type _type) { m_type = _type; }


  FORCEINLINE Type
    getType() const { return m_type; }

 protected:
  Type m_type;

};
}/// namespace bowEngineSDKs
