/************************************************************************/
/**
 * @file bowRasterizerState.h
 * @author Samuel G
 * @date 23/10/2026
 * @brief
 *  Base class for render target view , inherits from texture2D .
 */
 /*************************************************************************/
#pragma once

#include "bowTexture2D.h"

namespace bowEngineSDK
{
class RenderTargetView : public Texture2D
{
 public:
   /*
   * @brief
   *  Default constructor.
   */
   RenderTargetView() = default;

   /*
   * @brief
   *  Default destructor.
   */
   virtual
   ~RenderTargetView() = default;
};
}/// name space bowEngineSDK
