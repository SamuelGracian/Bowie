/************************************************************************/
/**
 * @file bowRasterizerState.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Base class for swap chain objects.
 */
 /*************************************************************************/
#pragma once

#include "bowCoreRequisites.h"
#include "bowRenderTargetView.h"

namespace bowEngineSDK
{
class SwapChain
{
 public:

   /**
   * @brief
   *  Default constructor.
   */
   SwapChain() = default;

   /**
   * @brief
   *  Default destructor.
   */
   virtual ~SwapChain() = default;

   /**
   * @brief
   *  Presents a rendered image to the user.
   * @param syncInterval:int that specifies how to synchronize presentation
      of a frame with the vertical blank.
      flags: flags for the swap chain.
   * @return none
   */
   virtual void
   present(uint32 syncInterval, uint32 flags) = 0;

   /**
   * @brief
   *  Gets the render target from the swap chain.
   * @param none
   * @return none
   */
   virtual SPtr <RenderTargetView>
   getRenderTargetView() = 0;

 protected:
   SPtr<RenderTargetView> m_renderTargetView;
   SPtr<RenderTargetView> m_renderTargetView1;

};
}/// name space bowEngineSDK
