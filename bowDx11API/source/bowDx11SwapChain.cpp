#include "bowDx11SwapChain.h"
#include "bowDx11RenderTargetView.h"

namespace bowEngineSDK
{
Dx11SwapChain::~Dx11SwapChain() {
  safeRelease(m_swapChain);
  safeRelease(m_backBufferRT);
}

void
Dx11SwapChain::present(uint32 syncIterval, uint32 flags) {
  if (m_swapChain == nullptr) {
    return;
  }

  if (!m_swapChain->Present(syncIterval, flags)) {
    return;
  }
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

}/// name space bowEngineSDK
