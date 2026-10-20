#pragma once 

#include <d3d11.h>
#include <dxgi.h>

namespace bowEngineSDK
{
template <typename T>
void safeRelease(T*& p) {
  if (p) {
    p->Release();
    p = nullptr;
  }
}
}
