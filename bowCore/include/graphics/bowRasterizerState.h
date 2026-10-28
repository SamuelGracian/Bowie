#pragma once

#include "bowGraphicsGenerals.h"

namespace bowEngineSDK
{
class RasterizerState
{
 public:
   RasterizerState() = default;
   ~RasterizerState() = default;

   FILL_MODE::E fillMode;
   CULL_MODE::E cullMode;
   bool depthClipEnable;
};
}/// namespace bowEngineSDK
