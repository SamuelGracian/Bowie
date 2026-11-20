#include "bowDx11RenderTargetView.h"

bowEngineSDK::Dx11RenderTargetView::~Dx11RenderTargetView() {
  safeRelease(m_renderTargetView);
  safeRelease(m_resourceView);
}
