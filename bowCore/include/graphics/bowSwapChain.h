#pragma once

#include "bowCoreRequisites.h"
#include "bowRenderTargetView.h"

namespace bowEngineSDK
{
class SwapChain
{
 public:

   /*
   * @brief
   *  Default constructor.
   */
   SwapChain() = default;

   /*
   * @brief
   *  Default destructor.
   */
   ~SwapChain() = default;

   virtual void
   present(uint32 syncInterval, uint32 flags) = 0;

   virtual SPtr <RenderTargetView>
   getRenderTargetView() = 0;

 protected:
   SPtr<RenderTargetView> m_renderTargetView;

};
}/// namespace bowEngineSDK
