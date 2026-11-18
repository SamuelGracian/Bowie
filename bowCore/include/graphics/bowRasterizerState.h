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
   *  Fill mode set as fill solid by default.
   *  Cull mode set as cull none by default.
   */
   RasterizerState() = default;

   /**
   * @brief
   *  Default destructor.
   */
   ~RasterizerState() = default;

 protected:
   FILL_MODE::E fillMode = FILL_MODE::kFILL_SOLID;
   CULL_MODE::E cullMode = CULL_MODE::kCULL_NONE;
   bool depthClipEnable = true;
};
}/// name space bowEngineSDK
