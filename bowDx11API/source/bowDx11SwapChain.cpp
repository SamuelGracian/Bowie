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

  if (FAILED( m_swapChain->Present(syncIterval, flags))) {
    return;
  }
}

SPtr<RenderTargetView>
Dx11SwapChain::getRenderTargetView() {
  if (m_renderTargetView == nullptr) {
    m_renderTargetView = makeShared<Dx11RenderTargetView>();

    auto p_renderTargetView = 
      staticPointerCast<Dx11RenderTargetView> (m_renderTargetView);

    if (m_backBufferRT != nullptr) {
      m_backBufferRT->AddRef();
      p_renderTargetView->m_renderTargetView = m_backBufferRT;
    }

    p_renderTargetView->m_renderTargetView = m_backBufferRT;
  }
  return m_renderTargetView;
}

}/// name space bowEngineSDK
