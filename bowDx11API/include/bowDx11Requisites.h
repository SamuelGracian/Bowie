#pragma once 

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11shader.h>
#include <Windows.h>

#include "bowGraphicsGenerals.h"

#include "bowCoreRequisites.h"

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
