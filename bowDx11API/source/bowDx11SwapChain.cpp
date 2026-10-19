#include "bowDx11SwapChain.h"
#include "bowDx11RenderTargetView.h"

namespace bowEngineSDK
{

void
Dx11SwapChain::present(uint32 syncIterval, uint32 flags) {
  m_swapChain->Present(syncIterval, flags);
}


SPtr<RenderTargetView>
Dx11SwapChain::getRenderTargetView() {
  if (m_renderTargetView == nullptr) {
    m_renderTargetView = std::make_shared<Dx11RenderTargetView>();

    auto p_renderTargetView = 
      std::reinterpret_pointer_cast<Dx11RenderTargetView> (m_renderTargetView);

    p_renderTargetView->m_renderTargetView = m_backBufferRT;
  }
  return m_renderTargetView;
}

}/// namespace bowEngineSDK
