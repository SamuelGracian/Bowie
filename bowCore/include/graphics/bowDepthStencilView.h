#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{

class DepthStencilView
{
 public:
  enum ClearFlags : uint8
  {
    Depth = 1,
    Stencil = 2
  };

  DepthStencilView() = default;
  ~DepthStencilView() = default;
};

}/// namespace bowEngineSDK