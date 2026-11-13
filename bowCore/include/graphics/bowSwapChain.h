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
   * @param
   * @return
   */
   virtual void
   present(uint32 syncInterval, uint32 flags) = 0;

   /**
   * @brief
   * @param
   * @return
   */
   virtual SPtr <RenderTargetView>
   getRenderTargetView() = 0;

 protected:
   SPtr<RenderTargetView> m_renderTargetView;
   SPtr<RenderTargetView> m_renderTargetView1;

};
}/// name space bowEngineSDK
