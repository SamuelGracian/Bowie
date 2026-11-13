/************************************************************************/
/**
 * @file bowRasterizerState.h
 * @author Samuel G
 * @date 23/10/2026
 * @brief
 *  Base class for Rasterizer State.
 */
 /*************************************************************************/
#pragma once

#include "bowGraphicsGenerals.h"

namespace bowEngineSDK
{
class RasterizerState
{
 public:
   /**
   * @brief
   *  Default constructor.
   */
   RasterizerState() = default;

   /**
   * @brief
   *  Default destructor.
   */
   ~RasterizerState() = default;

 protected:
   FILL_MODE::E fillMode;
   CULL_MODE::E cullMode;
   bool depthClipEnable;
};
}/// name space bowEngineSDK
