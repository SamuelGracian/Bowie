#pragma once 

#include "bowSwapChain.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11SwapChain : public SwapChain
{
 public:

   /*
   * @brief
   *  Default constructor, sets swap chain and backbuffer as nullptr.
   */
   Dx11SwapChain()
     : m_swapChain(nullptr) , m_backBufferRT(nullptr)
   {}

   /*
   * @brief
   *  Defualt destructor
   */
   ~SwapChain() = default;

   void
   present(uint32 syncInterval, uint32 flags) override;

   SPtr<RenderTargetView>
   getRenderTargetView() override;


 private:
   IDXGISwapChain* m_swapChain;
   ID3D11RenderTargetView* m_backBufferRT;
};
}/// namespace bowEngineSDK
