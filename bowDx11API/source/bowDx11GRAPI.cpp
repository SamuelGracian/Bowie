#include "bowDx11GraphicsAPI.h"

#include <iostream>

#include "bowDx11ConstBuffer.h"
#include "bowDx11IndexBuffer.h"
#include "bowDx11VertexBuffer.h"
#include "bowDx11SwapChain.h"
#include "bowDx11Helpers.h"

namespace bowEngineSDK
{
/*****************************************************/
/*  INTERNAL FUNCTIONS/ HELPERS  */
/*****************************************************/
IDXGISwapChain* 
Dx11GraphicsAPI::createSwapChainInternal(HWND hwnd, uint32_t width,
                                   uint32_t height, 
                                   GAPI_FORMAT::E format) {
  IDXGIFactory1* dxgiFactory1 = nullptr;

  IDXGIFactory2* dxgiFactory2 = nullptr;

  IDXGIDevice* dxgiDevice = nullptr;

  IDXGIAdapter* adapter = nullptr;

  IDXGISwapChain1* swapChain1 = nullptr;

  IDXGISwapChain* ResultSwapChain = nullptr;

  if (SUCCEEDED(m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)))) {
    if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter))) {
      HRESULT hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));

      if (SUCCEEDED(hr)) {
        hr = dxgiFactory1->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));

        if (SUCCEEDED(hr)) {

          DXGI_SWAP_CHAIN_DESC1 sd = {};

          sd.Width = width;
          sd.Height = height;
          sd.Format = Dx11Helpers::getDx11Format(format);
          sd.SampleDesc.Count = 1;
          sd.SampleDesc.Quality = 0;
          sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
          sd.BufferCount = 2;
          sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
          sd.Scaling = DXGI_SCALING_NONE;
          sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

          hr = dxgiFactory2->CreateSwapChainForHwnd(m_device, hwnd, &sd, nullptr, nullptr, &swapChain1);

          if (SUCCEEDED(hr)) {
            hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&ResultSwapChain));
          }
        }
        else {
          DXGI_SWAP_CHAIN_DESC sd = {};
          DXGI_FORMAT tempformat = Dx11Helpers::getDx11Format(format);

          sd.BufferCount = 1;
          sd.BufferDesc.Width = width;
          sd.BufferDesc.Height = height;
          sd.BufferDesc.Format = tempformat;
          sd.BufferDesc.RefreshRate.Numerator = 60;
          sd.BufferDesc.RefreshRate.Denominator = 1;
          sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
          sd.OutputWindow = hwnd;
          sd.SampleDesc.Count = 1;
          sd.SampleDesc.Quality = 0;
          sd.Windowed = TRUE;

          hr = dxgiFactory1->CreateSwapChain(m_device, &sd, &ResultSwapChain);
        }

        dxgiFactory1->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
      }
    }
  }

  safeRelease(dxgiFactory1);
  safeRelease(dxgiFactory2);
  safeRelease(dxgiDevice);
  safeRelease(adapter);
  safeRelease(swapChain1);

  return ResultSwapChain;
}


/*****************************************************/
bool
Dx11GraphicsAPI::init(WeakPtr<DisplaySurface> windowHandler) {
  if (windowHandler.expired()) {
    return false;
  }

  SPtr<DisplaySurface> window = windowHandler.lock();

  UINT createDeviceFlags = 0;

#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  // ---------------------------------------------------------
  // Feature Levels
  // ---------------------------------------------------------

  std::vector<D3D_FEATURE_LEVEL> featureLevels =
  {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
  };

  IDXGIFactory1* dxgiFactory = nullptr;

  HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), 
                                  reinterpret_cast<void**>(&dxgiFactory));

  if (FAILED(hr)) {
    return false;
  }

  IDXGIAdapter1* selectedAdapter = nullptr;

  for (UINT i = 0; ; ++i) {
    IDXGIAdapter1* adapter = nullptr;

    hr = dxgiFactory->EnumAdapters1(i, &adapter);

    if (hr == DXGI_ERROR_NOT_FOUND) {
      break;
    }

    if (FAILED(hr)) {
      continue;
    }

    DXGI_ADAPTER_DESC1 desc = {};
    adapter->GetDesc1(&desc);

    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
      adapter->Release();
      continue;
    }

    std::wstring adapterName(desc.Description); /// STRING?

    if (adapterName.find(L"NVIDIA") != std::wstring::npos) {
      selectedAdapter = adapter;

      break;
    }

    adapter->Release();
  }


  D3D_FEATURE_LEVEL resultFeatureLevel = {};

  if (selectedAdapter != nullptr) {
    hr = D3D11CreateDevice(
      selectedAdapter,
      D3D_DRIVER_TYPE_UNKNOWN,
      nullptr,
      createDeviceFlags,
      featureLevels.data(),
      static_cast<UINT>(featureLevels.size()),
      D3D11_SDK_VERSION,
      &m_device,
      &resultFeatureLevel,
      &m_immediateContext
    );

    if (SUCCEEDED(hr)) {

      selectedAdapter->Release();
      dxgiFactory->Release();


      D3D11_VIEWPORT viewport = {};

      /// Const???
      viewport.TopLeftX = 0.0f;
      viewport.TopLeftY = 0.0f;

      viewport.Width = static_cast<float>(window->getWidth());

      viewport.Height = static_cast<float>(window->getHeight());

      viewport.MinDepth = 0.0f;
      viewport.MaxDepth = 1.0f;

      m_immediateContext->RSSetViewports(
        1,
        &viewport
      );

      return true;
    }

    selectedAdapter->Release();
  }


  hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 
                         createDeviceFlags, featureLevels.data(), 
                         static_cast<UINT>(featureLevels.size()), 
                         D3D11_SDK_VERSION, &m_device, 
                         &resultFeatureLevel, &m_immediateContext);

  if (SUCCEEDED(hr)) {
    dxgiFactory->Release();

    D3D11_VIEWPORT viewport = {};

    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    viewport.Width = static_cast<float>(window->getWidth());

    viewport.Height = static_cast<float>(window->getHeight());

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_immediateContext->RSSetViewports(1, &viewport);

    return true;
  }


  dxgiFactory->Release();

  return false;
}

bool
Dx11GraphicsAPI::cleanUpResources() {

}

SPtr<SwapChain>
Dx11GraphicsAPI::createSwapChain(WeakPtr<DisplaySurface> _windowHandler, GAPI_FORMAT::E _format) {
  SPtr<Dx11SwapChain> SChain = nullptr;

  if (_windowHandler.expired()) {
    std::cout << "Handle window expired" << std::endl;
    return SChain;
  }

  std::shared_ptr<DisplaySurface> tempSurface = _windowHandler.lock();

  if (auto* ResultSwapChain = CreateSwapChain_internal(tempSurface->getHandle(), 
                                                       tempSurface->getClientWidth(), 
                                                       tempSurface->getClientHeight(), format)) {
    if (auto* ResultRT = CreateBackBufferRT_internal(ResultSwapChain)) {
      SChain = std::make_shared<Dx11SwapChain>();

      SChain->m_BackBufferRT = ResultRT;

      SChain->m_swapChain = ResultSwapChain;
    }
  }
  return SChain;
}

SPtr<ConstBuffer>
Dx11GraphicsAPI::createConstBuffer(const uint32 byteWitdh,
                             const uint32 slot, void* data) {
  ID3D11Buffer* Rawbuffer = nullptr;
  D3D11_BUFFER_DESC bd = {};
  if (bytewidth != 0) {
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = bytewidth;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
  }

  if (SUCCEEDED((m_device->CreateBuffer(&bd, nullptr, &Rawbuffer))))

  {
    auto buffer = std::make_shared<Dx11ConstantBuffer>();
    buffer->m_buffer = Rawbuffer;
    buffer->SetByteWidth(bytewidth);
    buffer->SetSlot(slot);

    //ASSIGN_DEBUG_NAME(buffer.get(), Rawbuffer);
    return buffer;
  }
  return nullptr;
}

SPtr<Indexbuffer>
Dx11GraphicsAPI::createIndexBuffer() {
  BOW_ASSERT(bytewidth != 0);
  D3D11_BUFFER_DESC bd = {};
  ID3D11Buffer* Rawbuffer = nullptr;
  D3D11_SUBRESOURCE_DATA InitData = {};
  auto ResultBuffer = std::make_shared<Dx11IndexBuffer>();

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = bytewidth;
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  InitData.pSysMem = data;

  if (SUCCEEDED(m_device->CreateBuffer(&bd, &InitData, &Rawbuffer))) {
    ResultBuffer->m_buffer = Rawbuffer;
  }

  return ResultBuffer;
}

SPtr<VertexBuffer>
Dx11GraphicsAPI::createVertexBuffer() {
  ID3D11Buffer* Rawbuffer = nullptr;
  std::shared_ptr<Dx11VertexBuffer> ResultBuffer;

  D3D11_BUFFER_DESC bd = {};
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = bytewidth;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA InitData = {};
  InitData.pSysMem = vertices;

  if (SUCCEEDED(m_device->CreateBuffer(&bd, &InitData, &Rawbuffer))) {
    ResultBuffer = std::make_shared<Dx11VertexBuffer>();
    ResultBuffer->m_buffer = Rawbuffer;
  }
  return ResultBuffer;
}

void
Dx11GraphicsAPI::setConstBuffer(WeakPtr<ConstBuffer> buffer) {
  if (m_immediateContext == nullptr || buffer.expired()) {
    return;
  }
  auto pbuffer = std::static_pointer_cast<Dx11ConstantBuffer>(buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->GetSlot() >= BUFFER_HIGHER_AVAILABLE_SLOT) {
    return;
  }

  m_immediateContext->VSSetConstantBuffers(pbuffer->GetSlot(), 1, &pbuffer->m_buffer);
  m_immediateContext->PSSetConstantBuffers(pbuffer->GetSlot(), 1, &pbuffer->m_buffer);
}

void 
Dx11GraphicsAPI::setIndexBuffer(WeakPtr<Indexbuffer> buffer) {
  if (m_immediateContext == nullptr || buffer.expired()) {
    return;
  }

  auto pbuffer = std::static_pointer_cast<Dx11IndexBuffer> (buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr) {
    return;
  }

  m_immediateContext->IASetIndexBuffer(pbuffer->m_buffer, DXGI_FORMAT_R16_UINT, 0);
}

void
Dx11GraphicsAPI::updateConstBuffer(WeakPtr<ConstBuffer> buffer,
                             const uint32 byteWitdth, void* data) {
  if (m_immediateContext == nullptr || buffer.expired() || Data == nullptr) {
    return;
  }
  auto pbuffer = std::static_pointer_cast <Dx11ConstantBuffer> (buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->GetByteWidth() != bytewidth) {
    return;
  }

  m_immediateContext->UpdateSubresource(pbuffer->m_buffer, 0, nullptr, Data, 0, 0);
}



}