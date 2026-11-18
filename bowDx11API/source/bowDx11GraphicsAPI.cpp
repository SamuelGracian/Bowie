#include "bowDx11GraphicsAPI.h"

#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <iostream>
#include <cstring>

#include "bowDx11ConstBuffer.h"
#include "bowDx11DepthStencilView.h"
#include "bowDx11IndexBuffer.h"
#include "bowDx11PixelShader.h"
#include "bowDx11RasterizerState.h"
#include "bowDx11RenderTargetView.h"
#include "bowDx11Texture2D.h"
#include "bowDx11Topology.h"
#include "bowDx11SamplerState.h"
#include "bowDx11SwapChain.h"
#include "bowDx11VertexBuffer.h"
#include "bowDx11VertexShader.h"
#include "bowDx11ViewPort.h"
#include "bowMath.h"
#include "bowMatrix.h"
#include "bowVector4.h"
#include "bowWindow.h"


namespace bowEngineSDK
{
/*****************************************************/
/*  INTERNAL FUNCTIONS/ HELPERS  */
/*****************************************************/

DXGI_FORMAT
Dx11GraphicsAPI::getDx11FormatInternal(TEXTURE_FORMAT::E _format) const {
  switch (_format) {

  case bowEngineSDK::TEXTURE_FORMAT::kFORMAT_UNKNOWN:
    return DXGI_FORMAT_UNKNOWN;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kD24_UNORM_S8_UINT:
    return DXGI_FORMAT_D24_UNORM_S8_UINT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR32_FLOAT:
    return DXGI_FORMAT_R32_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR8G8B8A8_UNORM:
    return DXGI_FORMAT_R8G8B8A8_UNORM;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kB8G8R8A8_UNORM:
    return DXGI_FORMAT_B8G8R8A8_UNORM;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR16G16B16A16_FLOAT:
    return DXGI_FORMAT_R16G16B16A16_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kD32_FLOAT:
    return DXGI_FORMAT_D32_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR8_UNORM:
    return DXGI_FORMAT_R8_UNORM;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR8G8_UNORM:
    return DXGI_FORMAT_R8G8_UNORM;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR16_FLOAT:
    return DXGI_FORMAT_R16_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR16G16_FLOAT:
    return DXGI_FORMAT_R16G16_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR32G32B32A32_FLOAT:
    return DXGI_FORMAT_R32G32B32A32_FLOAT;
    break;

  case bowEngineSDK::TEXTURE_FORMAT::kR32_UINT:
    return DXGI_FORMAT_R32_UINT;
    break;

  default:
    return DXGI_FORMAT_UNKNOWN;
    break;
  }
}


uint32
Dx11GraphicsAPI::getDx11BindFlagsInternal(const uint32 _bindFlag) const {
  uint32 ResultFlags = 0;

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kBIND_CONSTANT_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_CONSTANT_BUFFER;
  }

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kBIND_INDEX_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_INDEX_BUFFER;
  }

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kBIND_VERTEX_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_VERTEX_BUFFER;
  }

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kDEPTH_STENCIL) != 0) {
    ResultFlags += D3D11_BIND_DEPTH_STENCIL;
  }

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kRENDER_TARGET) != 0) {
    ResultFlags += D3D11_BIND_RENDER_TARGET;
  }

  if ((_bindFlag & GRAPHICS_API_BIND_FLAGS::kSHADER_RESOURCE) != 0) {
    ResultFlags += D3D11_BIND_SHADER_RESOURCE;
  }

  return ResultFlags;
}

const char*
Dx11GraphicsAPI::getShaderModelInternal(SHADER_TYPE::E _shaderType,
                                        uint32 _shaderModel) const {
  static String ResultShader;

  String modelVersion = std::to_string(_shaderModel) + "_0";

  switch (_shaderType) {
  case SHADER_TYPE::E::kVERTEX_SHADER:
    ResultShader = "vs_" + modelVersion;
    break;

  case SHADER_TYPE::E::kPIXEL_SHADER:
    ResultShader = "ps_" + modelVersion;
    break;

  default:
    ResultShader = "vs_4_0";
    break;
  }

  return ResultShader.c_str();
}

IDXGISwapChain* 
Dx11GraphicsAPI::createSwapChainInternal(HWND hwnd, uint32 width,uint32 height,
                                         TEXTURE_FORMAT::E format) {
  IDXGIFactory1* dxgiFactory1 = nullptr;

  IDXGIFactory2* dxgiFactory2 = nullptr;

  IDXGIDevice* dxgiDevice = nullptr;

  IDXGIAdapter* adapter = nullptr;

  IDXGISwapChain1* swapChain1 = nullptr;

  IDXGISwapChain* ResultSwapChain = nullptr;

  if (SUCCEEDED(m_device->QueryInterface(__uuidof(IDXGIDevice),
                                         reinterpret_cast<void**>(&dxgiDevice)))) {

    if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter))) {
      HRESULT hr = adapter->GetParent(__uuidof(IDXGIFactory1),
                                      reinterpret_cast<void**>(&dxgiFactory1));

      if (SUCCEEDED(hr)) {
        hr = dxgiFactory1->QueryInterface(__uuidof(IDXGIFactory2),
                                          reinterpret_cast<void**>(&dxgiFactory2));

        if (SUCCEEDED(hr)) {

          DXGI_SWAP_CHAIN_DESC1 sd = {};

          sd.Width = width;
          sd.Height = height;
          sd.Format = getDx11FormatInternal(format);
          sd.SampleDesc.Count = 1;
          sd.SampleDesc.Quality = 0;
          sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
          sd.BufferCount = 2;
          sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
          sd.Scaling = DXGI_SCALING_NONE;
          sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

          hr = dxgiFactory2->CreateSwapChainForHwnd(m_device,
                                                    hwnd,
                                                    &sd,
                                                    nullptr,
                                                    nullptr,
                                                    &swapChain1);

          if (SUCCEEDED(hr)) {
            hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain),
                                            reinterpret_cast<void**>(&ResultSwapChain));
          }
        }
        else {
          DXGI_SWAP_CHAIN_DESC sd = {};
          DXGI_FORMAT tempformat = getDx11FormatInternal(format);

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

          hr = dxgiFactory1->CreateSwapChain(m_device,
                                             &sd,
                                             &ResultSwapChain);
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

ID3D11RenderTargetView*
Dx11GraphicsAPI::createBackBufferRTInternal(IDXGISwapChain* _swapChain) {

  ID3D11Texture2D* resultTextureRT = nullptr;

  ID3D11RenderTargetView* resultRT = nullptr;

  if (_swapChain != nullptr && m_device != nullptr) {

    if (SUCCEEDED(_swapChain->GetBuffer(0,
                                        __uuidof(ID3D11Texture2D),
                                        reinterpret_cast<void**>(&resultTextureRT)))) {

      m_device->CreateRenderTargetView(resultTextureRT,
                                       nullptr,
                                       &resultRT);
    }
  }
  safeRelease(resultTextureRT);

  return resultRT;
}

ID3D11Texture2D*
Dx11GraphicsAPI::createTexture2DInternal(uint32 _width,
                                         uint32 _height,
                                         const TEXTURE_FORMAT::E _format,
                                         uint32 _bindFlags) {
  
  ID3D11Texture2D* resultTexture = nullptr;

  if (_width != 0 && _height != 0
      && _format != TEXTURE_FORMAT::kFORMAT_UNKNOWN
      && m_device != nullptr) {
    D3D11_TEXTURE2D_DESC descTexture = {};
    descTexture.Width = _width;
    descTexture.Height = _height;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = getDx11FormatInternal(_format);
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = getDx11BindFlagsInternal(_bindFlags);
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;
    m_device->CreateTexture2D(&descTexture,
                              nullptr,
                              &resultTexture);
  }
  return resultTexture;
}

ID3DBlob*
Dx11GraphicsAPI::compileShaderInternal(const String& _shaderCode,
                                       const String& _entryPoint,
                                       Vector<String>_defines,
                                       SHADER_TYPE::E _shaderType,
                                       uint32 _shaderModel) const {
  ID3DBlob* errorBlob = nullptr;
  ID3DBlob* binaryBlob = nullptr;

  if (!_shaderCode.empty() && !_entryPoint.empty()) {
    String finalShaderCore;

    uint32 dwShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef BOW_DEBUG_MODE
    /*
    * Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    * Settings this flag improves the shader debugging experience, but still
    * allows the shader to be optimized and run exactly the way they will run 
    * in the release configuration of this program.
    */
    dwShaderFlag |= D3DCOMPILE_DEBUG;
    dwShaderFlag |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // BOW_DEBUG_MODE

    for (String& macro : _defines) {
      finalShaderCore += (macro = '\n');
    }

    finalShaderCore += _shaderCode;

    if (FAILED(D3DCompile(finalShaderCore.c_str(),
                          finalShaderCore.length(),
                          nullptr,
                          nullptr,
                          nullptr,
                          _entryPoint.c_str(),
                          getShaderModelInternal(_shaderType, _shaderModel), 
                          dwShaderFlag,
                          0,
                          &binaryBlob,
                          &errorBlob))) {
      if (errorBlob) {
        BOW_LOG_ERROR("Shader compilation error" <<
          reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
      }
    }
  }

  safeRelease(errorBlob);
  return binaryBlob;
}

Vector<D3D11_INPUT_ELEMENT_DESC>
Dx11GraphicsAPI::createInputLayoutInternal(ID3D11ShaderReflection* _reflection) 
const {
  Vector<D3D11_INPUT_ELEMENT_DESC>inputLayoutDesc;

  if (_reflection) {
    D3D11_SHADER_DESC shaderDesc;
    _reflection->GetDesc(&shaderDesc);

    inputLayoutDesc.reserve(shaderDesc.InputParameters);

    for (uint32 i = 0; i < shaderDesc.InputParameters; ++i) {
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      _reflection->GetInputParameterDesc(i, &paramDesc);

      D3D11_INPUT_ELEMENT_DESC elementDesc = {};
      elementDesc.SemanticName = paramDesc.SemanticName;
      elementDesc.SemanticIndex = paramDesc.SemanticIndex;
      elementDesc.InputSlot = 0;
      elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      elementDesc.InstanceDataStepRate = 0;

      uint32 componentCount = 0;
      if (paramDesc.Mask == 1) {
        componentCount = 1;
      }

      else if (paramDesc.Mask <= 3) {
        componentCount = 2;
      }
      else if (paramDesc.Mask <= 7) {
        componentCount = 3;
      }
      else if (paramDesc.Mask <= 15) {
        componentCount = 4;
      }

      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        if (componentCount == 1) {
          elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (componentCount == 2) {
          elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (componentCount == 3) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (componentCount == 4) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        if (componentCount == 1) {
          elementDesc.Format = DXGI_FORMAT_R32_UINT;
        }
        else if (componentCount == 2) {
          elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        }
        else if (componentCount == 3) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        }
        else if (componentCount == 4) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        }
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
        if (componentCount == 1) {
          elementDesc.Format = DXGI_FORMAT_R32_SINT;
        }
        else if (componentCount == 2) {
          elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        }
        else if (componentCount == 3) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        }
        else if (componentCount == 4) {
          elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        }
      }

      inputLayoutDesc.push_back(elementDesc);
    }
  }
  return inputLayoutDesc;
}

D3D11_FILL_MODE
Dx11GraphicsAPI::getFillModeInternal(FILL_MODE::E _fillMode) const {
  switch (_fillMode) {
  default:
    return D3D11_FILL_MODE::D3D11_FILL_SOLID;
    break;

  case FILL_MODE::kFILL_WIREFRAME:
    return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    break;
  }
}

D3D11_CULL_MODE
Dx11GraphicsAPI::getCullModeInternal(CULL_MODE::E _cullMode) const {
  switch (_cullMode) {
  default:
    return D3D11_CULL_MODE::D3D11_CULL_NONE;
    break;

  case CULL_MODE::kCULL_BACK:
    return D3D11_CULL_MODE::D3D11_CULL_BACK;
    break;

  case CULL_MODE::kCULL_FRONT:
    return D3D11_CULL_MODE::D3D11_CULL_FRONT;
    break;
  }
}


Dx11GraphicsAPI::~Dx11GraphicsAPI() {
  cleanUpResources();
}

/*****************************************************/
bool
Dx11GraphicsAPI::init(WeakPtr<DisplaySurface>windowHandler) {
  if (windowHandler.expired()) {
    return false;
  }

  SPtr<DisplaySurface>window = windowHandler.lock();

  uint32 createDeviceFlags = 0;

#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  // ---------------------------------------------------------
  // Feature Levels
  // ---------------------------------------------------------

  Vector<D3D_FEATURE_LEVEL>featureLevels =
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
  IDXGIAdapter1* adapter = nullptr;
  SIZE_T bestDedicatedVideoMemory = 0;

  for (uint32 i = 0; SUCCEEDED(dxgiFactory->EnumAdapters1(i, &adapter)); ++i) {

    DXGI_ADAPTER_DESC1 desc = {};
    adapter->GetDesc1(&desc);

    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
      adapter->Release();
      adapter = nullptr;
      continue;
    }

    if (desc.DedicatedVideoMemory > bestDedicatedVideoMemory) {

      if (nullptr != selectedAdapter) {
        selectedAdapter->Release();
      }

      bestDedicatedVideoMemory = desc.DedicatedVideoMemory;
      selectedAdapter = adapter;
    }
    else {
      adapter->Release();
    }
    
    adapter = nullptr;
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

void
Dx11GraphicsAPI::draw(uint32 _vertexCount, uint32 _startVertexLocation) {
  if (m_immediateContext) {
    m_immediateContext->DrawIndexed(_vertexCount,
                                    _startVertexLocation,
                                    0);
  }
}

void
Dx11GraphicsAPI::cleanUpResources(){
  if (m_immediateContext != nullptr) {
    m_immediateContext->ClearState();
    m_immediateContext->Flush();
    safeRelease(m_immediateContext);
  }
  safeRelease(m_device);
}

SPtr<SwapChain>
Dx11GraphicsAPI::createSwapChain(WeakPtr<DisplaySurface> _windowHandler,
                                 TEXTURE_FORMAT::E _format) {
  SPtr<Dx11SwapChain> SChain = nullptr;

  if (_windowHandler.expired()) {
    BOW_LOG_ERROR("Handle window expired");
    return SChain;
  }

  SPtr<DisplaySurface> tempSurface = _windowHandler.lock();
  HWND tempHandler = reinterpret_cast<HWND>(tempSurface->getHandle());

  if (auto* ResultSwapChain = createSwapChainInternal(tempHandler,
                                                tempSurface->getClientWidth(),
                                                tempSurface->getClientHeight(),
                                                _format)) {

    SChain = MakeShared<Dx11SwapChain>();
    SChain->m_swapChain = ResultSwapChain;

    if (ID3D11RenderTargetView* ResultRT =
        createBackBufferRTInternal(ResultSwapChain)) {

      SChain->m_backBufferRT = ResultRT;
    }
    else {
      BOW_LOG_ERROR("Failed to create BackBuffer RenderTargetView");
    }
  }

  return SChain;
}

SPtr<ConstBuffer>
Dx11GraphicsAPI::createConstBuffer(const uint32 _byteWidth,
                                   const uint32 slot) {
  if (m_device == nullptr) {
    BOW_LOG_ERROR("Create const buffer: device = nullptr");
    return nullptr;
  }
  ID3D11Buffer* Rawbuffer = nullptr;
  D3D11_BUFFER_DESC bd = {};
  if (_byteWidth != 0) {
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _byteWidth;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
  }

  if (SUCCEEDED((m_device->CreateBuffer(&bd, nullptr, &Rawbuffer))))
  {
    SPtr<Dx11ConstBuffer> buffer =
        MakeShared<Dx11ConstBuffer>(_byteWidth, slot);
    buffer->m_buffer = Rawbuffer;
    return buffer;
  }
  return nullptr;
}

SPtr<IndexBuffer>
Dx11GraphicsAPI::createIndexBuffer(const uint32 _byteWidth, void* _data) {
  if (m_device == nullptr) {
    BOW_LOG_ERROR("Create index buffer: device = nullptr");
    return nullptr;
  }

  BOW_ASSERT(_byteWidth != 0);
  D3D11_BUFFER_DESC bd = {};
  ID3D11Buffer* Rawbuffer = nullptr;
  D3D11_SUBRESOURCE_DATA InitData = {};
  SPtr<Dx11IndexBuffer> ResultBuffer =
    MakeShared<Dx11IndexBuffer>(_byteWidth);

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = _byteWidth;
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  InitData.pSysMem = _data;

  if (_data == nullptr) {
    if (SUCCEEDED(m_device->CreateBuffer(&bd,
                                         nullptr,
                                         &Rawbuffer))) {
      ResultBuffer->m_buffer = Rawbuffer;
      return ResultBuffer;
    }
  }

  else {
    if (SUCCEEDED(m_device->CreateBuffer(&bd,
                                         &InitData,
                                         &Rawbuffer))) {
      ResultBuffer->m_buffer = Rawbuffer;
      return ResultBuffer;
    }
  }
  return nullptr;
}

SPtr<VertexBuffer>
Dx11GraphicsAPI::createVertexBuffer(const uint32 _byteWidth,
                                    const void* _vertices) {
  if (m_device == nullptr) {
    BOW_LOG_ERROR("Create vertex buffer: device = nullptr");
    return nullptr;
  }
  ID3D11Buffer* Rawbuffer = nullptr;
  SPtr<Dx11VertexBuffer>ResultBuffer;

  D3D11_BUFFER_DESC bd = {};
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = _byteWidth;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA InitData = {};
  InitData.pSysMem = _vertices;

  if (SUCCEEDED(m_device->CreateBuffer(&bd,
                                       &InitData,
                                       &Rawbuffer))) {
    ResultBuffer = MakeShared<Dx11VertexBuffer>(_byteWidth);
    ResultBuffer->m_buffer = Rawbuffer;
  }
  return ResultBuffer;
}

void
Dx11GraphicsAPI::setConstBuffer(WeakPtr<ConstBuffer>buffer) {
  if (m_immediateContext == nullptr || buffer.expired()) {
    return;
  }
  SPtr<Dx11ConstBuffer>pbuffer =
    StaticPointerCast<Dx11ConstBuffer>(buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->getSlot() 
      >= BUFFER_HIGHER_AVAILABLE_SLOT) {
    return;
  }

  m_immediateContext->VSSetConstantBuffers(pbuffer->getSlot(),
                                           1,
                                           &pbuffer->m_buffer);

  m_immediateContext->PSSetConstantBuffers(pbuffer->getSlot(),
                                           1,
                                           &pbuffer->m_buffer);
}

void
Dx11GraphicsAPI::setVertexBuffer(WeakPtr<VertexBuffer>_buffer, uint32 _stride,
                                 uint32 _offset) {
  if (m_immediateContext == nullptr || _buffer.expired()) {
    BOW_LOG_ERROR("set vertex buffer, context or buffer = nullptr");
    return;
  }
    auto pBuffer = StaticPointerCast<Dx11VertexBuffer>(_buffer.lock());

    if (pBuffer && pBuffer->m_buffer) {
      m_immediateContext->IASetVertexBuffers(0,
                                             1,
                                             &pBuffer->m_buffer,
                                             &_stride,
                                             &_offset);
    }
  
  return;
}

void
Dx11GraphicsAPI::setIndexBuffer(WeakPtr<IndexBuffer>buffer) {
  if (m_immediateContext == nullptr || buffer.expired()) {
    return;
  }

  auto pbuffer = StaticPointerCast<Dx11IndexBuffer>(buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr) {
    return;
  }

  m_immediateContext->IASetIndexBuffer(pbuffer->m_buffer,
                                       DXGI_FORMAT_R16_UINT,
                                       0);
}

void
Dx11GraphicsAPI::updateConstBuffer(WeakPtr<ConstBuffer>_buffer,
                             const uint32 _byteWidth, void* _data) {
  if (m_immediateContext == nullptr || _buffer.expired() || _data == nullptr) {
    return;
  }
  auto pbuffer = StaticPointerCast <Dx11ConstBuffer>(_buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr ||
      pbuffer->getByteWidth() != _byteWidth) {
    return;
  }
  /// To do: update const buffer byte width 
  m_immediateContext->UpdateSubresource(pbuffer->m_buffer,
                                        0,
                                        nullptr,
                                        _data,
                                        0,
                                        0);
}

SPtr<Topology>
Dx11GraphicsAPI::createTopology(TOPOLOGY_TYPE::E _type) {
  auto topo = MakeShared<Dx11Topology>();

  topo->setType(_type);

  switch (_type) {
  case bowEngineSDK::TOPOLOGY_TYPE::kTriangleList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;

  case bowEngineSDK::TOPOLOGY_TYPE::kTriangleStrip:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    break;

  case bowEngineSDK::TOPOLOGY_TYPE::kLineList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    break;

  case bowEngineSDK::TOPOLOGY_TYPE::kPointList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    break;

  default:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;
  }

  return topo;
}

void
Dx11GraphicsAPI::setTopology(WeakPtr<Topology>_topology){
  if (m_immediateContext == nullptr || _topology.expired()){
    return;
   }

  auto pTopo = StaticPointerCast<Dx11Topology>(_topology.lock());
  if (pTopo == nullptr) {
    return;
  }

  m_immediateContext->IASetPrimitiveTopology(pTopo->dx11Topology);
}

SPtr<DepthStencilView>
Dx11GraphicsAPI::createDepthStencil(uint32 _width, uint32 _height,
                                    const TEXTURE_FORMAT::E _format) {
  
  SPtr<Dx11DepthStencilView>resultDS = nullptr;
  ID3D11DepthStencilView* resultDepthStencilView = nullptr;
  ID3D11Texture2D* depthStencilTexture = nullptr;

  if (m_device != nullptr && _width != 0.0f && _height != 0.0
      && _format != TEXTURE_FORMAT::kFORMAT_UNKNOWN) {

    depthStencilTexture = createTexture2DInternal(_width,
                                                  _height,
                                                  _format,
                                                  GRAPHICS_API_BIND_FLAGS::kDEPTH_STENCIL);

    if (depthStencilTexture != nullptr){
      D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
      descDSV.Format = getDx11FormatInternal(_format);
      descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
      descDSV.Texture2D.MipSlice = 0;

      if (SUCCEEDED(m_device->CreateDepthStencilView(depthStencilTexture,
                                                     &descDSV,
                                                     &resultDepthStencilView))) {
        resultDS = MakeShared<Dx11DepthStencilView>();
        resultDS->m_depthStencilView = resultDepthStencilView;
      }
    }
  }
  safeRelease(depthStencilTexture);
  return resultDS;
}

SPtr<ViewPort>
Dx11GraphicsAPI::createViewPort(float width, float height, float minDepth,
                                float maxDepth, float topLeftX, float topLeftY) {


  if (width <= 0.0f || height <= 0.0f || minDepth < 0.0f || maxDepth > 1.0f ||
      minDepth > maxDepth) {
    return nullptr;
  }

  D3D11_VIEWPORT dxViewport = {};
  dxViewport.Width = width;
  dxViewport.Height = height;
  dxViewport.MinDepth = minDepth;
  dxViewport.MaxDepth = maxDepth;
  dxViewport.TopLeftX = topLeftX;
  dxViewport.TopLeftY = topLeftY;

  return MakeShared<Dx11ViewPort>(width,
                                        height,
                                        minDepth,
                                        maxDepth,
                                        topLeftX,
                                        topLeftY);
}


bool
Dx11GraphicsAPI::setViewPort(WeakPtr<ViewPort>viewPort) {
  if ( m_immediateContext == nullptr) {
    BOW_LOG_ERROR(
      "createViewPort function: m_immediatecontext = nullptr");
    return false;
  }

  const auto viewport = viewPort.lock();

  if (viewport == nullptr) {
    BOW_LOG_ERROR( "setViewPort: view port is nullptr" );
    return false;
  }
  const auto dxViewport =
    std::static_pointer_cast<Dx11ViewPort>(viewport);

  if (dxViewport == nullptr) {
    BOW_LOG_ERROR("setViewPort: invalid view port type");
    return false;
  }

  m_immediateContext->RSSetViewports(1,
                                     &dxViewport->m_viewPort);

  return true;
}

SPtr<VertexShader>
Dx11GraphicsAPI::createVertexShader(const String& shaderCode,
                                    const String& entryPoint,
                                    Vector<String>& defines,
                                    uint32 shadermodel) {
  ID3DBlob* binaryBlob = nullptr;
  ID3D11ShaderReflection* shaderReflection = nullptr;
  ID3D11VertexShader* resultShader = nullptr;
  ID3D11InputLayout* resultLayout = nullptr;

  binaryBlob = compileShaderInternal(shaderCode,
                                     entryPoint,
                                     defines,
                                     SHADER_TYPE::kVERTEX_SHADER,
                                     shadermodel);

  SPtr<Dx11VertexShader>resultVShader = nullptr;

  if (binaryBlob == nullptr || m_device == nullptr) {
    return nullptr;
  }

  if (!SUCCEEDED(D3DReflect(binaryBlob->GetBufferPointer(),
                            binaryBlob->GetBufferSize(),
                            IID_ID3D11ShaderReflection,
                            (void**)&shaderReflection))) {
    BOW_LOG_ERROR("D3Drefelct failed");
    safeRelease(binaryBlob);
    return nullptr;
  }
  const Vector<D3D11_INPUT_ELEMENT_DESC> desc =
    createInputLayoutInternal(shaderReflection);

  const uint32 numElements = static_cast<uint32>(desc.size());

  if (SUCCEEDED(m_device->CreateVertexShader(binaryBlob->GetBufferPointer(),
                                             binaryBlob->GetBufferSize(),
                                             nullptr,
                                             &resultShader))) {

    resultVShader = MakeShared<Dx11VertexShader>();
    resultVShader->m_shader = resultShader;

    if (SUCCEEDED(m_device->CreateInputLayout(desc.data(),
                                             numElements,
                                             binaryBlob->GetBufferPointer(),
                                             binaryBlob->GetBufferSize(),
                                             &resultLayout))) {

      resultVShader->m_InputLayout = resultLayout;
    }
    else {
      BOW_LOG_ERROR("CreateInputLayout failed");
    }
  }
  else {
    BOW_LOG_ERROR("CreateVertexShader failed");
  }
  return resultVShader;
}

void
Dx11GraphicsAPI::setVertexShader(WeakPtr<VertexShader>shader) {
  if (shader.expired()) {
    return;
  }

  auto resultShader = 
    std::static_pointer_cast<Dx11VertexShader>(shader.lock());

  if (resultShader && m_immediateContext) {
    m_immediateContext->IASetInputLayout(resultShader->m_InputLayout);
    m_immediateContext->VSSetShader(resultShader->m_shader,
                                    nullptr,
                                    0);
  }
}

SPtr<PixelShader>
Dx11GraphicsAPI::createPixelShader(const String& shaderCode,
                                   const String& entryPoint,
                                   Vector<String>& defines,
                                   uint32 shaderModel) {
  ID3DBlob* binaryBlob = nullptr;
  ID3D11PixelShader* resultShader = nullptr;
  SPtr<Dx11PixelShader>shaderPtr = nullptr;

  if (m_device == nullptr) {
    BOW_LOG_ERROR("createPixelShader function, error m_device = nullptr");
    return nullptr;
  }

  binaryBlob = compileShaderInternal(shaderCode,
                                     entryPoint,
                                     defines,
                                     SHADER_TYPE::kPIXEL_SHADER,
                                     shaderModel);

  if (binaryBlob == nullptr) {
    BOW_LOG_ERROR("createPixelShader function, binary blob = nullptr");
    return nullptr;
  }
  
  if (SUCCEEDED(m_device->CreatePixelShader(binaryBlob->GetBufferPointer(),
                                            binaryBlob->GetBufferSize(),
                                            nullptr, &resultShader))) {
    shaderPtr = MakeShared<Dx11PixelShader>();

    shaderPtr->pixShader = resultShader;
  }
  safeRelease(binaryBlob);
  return shaderPtr;
}

void Dx11GraphicsAPI::setPixelShader(WeakPtr<PixelShader>shader) {
  if (shader.expired() || m_immediateContext == nullptr) {
    BOW_LOG_ERROR(
      "setPixelShader function" << "\n" << 
      "shader or immediate context = nullptr");
    return;
  }
  auto p_Ps = std::static_pointer_cast<Dx11PixelShader>(shader.lock());
  m_immediateContext->PSSetShader(p_Ps->pixShader, nullptr, 0);
}

SPtr<RasterizerState>
Dx11GraphicsAPI::createRasterizerState(CULL_MODE::E cullMode,
                                       FILL_MODE::E fillMode,
                                       bool depthClip) {
  if (m_device == nullptr) {
    BOW_LOG_ERROR(
      "createRasterizerState function, m_device = nullptr");
    return nullptr;
  }
  auto rasterizerState = MakeShared<Dx11RasterizerState>();

  D3D11_RASTERIZER_DESC  desc = {};

  desc.FillMode = getFillModeInternal(fillMode);
  desc.CullMode = getCullModeInternal(cullMode);
  desc.DepthClipEnable = depthClip;
  //default values
  desc.FrontCounterClockwise = FALSE;
  desc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
  desc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
  desc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
  desc.ScissorEnable = FALSE;
  desc.MultisampleEnable = FALSE;
  desc.AntialiasedLineEnable = FALSE;

  ID3D11RasterizerState* rawRasterizer = nullptr;

  if (SUCCEEDED(m_device->CreateRasterizerState(&desc, &rawRasterizer))) {
    rasterizerState->rasterizer = rawRasterizer;
    rasterizerState->cullMode = cullMode;
    rasterizerState->fillMode = fillMode;
    rasterizerState->depthClipEnable = depthClip;

    return rasterizerState;
  }

  return nullptr;

}

void
Dx11GraphicsAPI::setRasterizerState(WeakPtr<RasterizerState>rasterizer) {
  if (m_device == nullptr || rasterizer.expired()) {
    return;
  }
  auto dxrasterizer = 
    std::static_pointer_cast <Dx11RasterizerState>(rasterizer.lock());

  if (dxrasterizer && dxrasterizer->rasterizer) {
    m_immediateContext->RSSetState(dxrasterizer->rasterizer);
  }
}

SPtr<RenderTargetView>
Dx11GraphicsAPI::createRenderTargetView(uint32 width,
                                        uint32 height,
                                        TEXTURE_FORMAT::E format) {

  SPtr<Dx11RenderTargetView>resultRTV = nullptr;
  ID3D11Texture2D* renderTargetTexture = nullptr;
  ID3D11RenderTargetView* resultView = nullptr;
  ID3D11ShaderResourceView* resourceView = nullptr;


  if (m_device != nullptr && width != 0 && height != 0 && 
      format != TEXTURE_FORMAT::kFORMAT_UNKNOWN) {
    renderTargetTexture = createTexture2DInternal(
      width,
      height,
      format,
      GRAPHICS_API_BIND_FLAGS::kRENDER_TARGET |
      GRAPHICS_API_BIND_FLAGS::kSHADER_RESOURCE);

    if (renderTargetTexture) {
      if (SUCCEEDED(m_device->CreateRenderTargetView(renderTargetTexture,
                                                     nullptr, &resultView))) {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = getDx11FormatInternal(format);
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;

        if (SUCCEEDED(m_device->CreateShaderResourceView(renderTargetTexture,
                                                         &srvDesc,
                                                         &resourceView))) {
          resultRTV = MakeShared<Dx11RenderTargetView>();
          resultRTV->m_renderTargetView = resultView;
          resultRTV->m_resourceView = resourceView;
        }

      }
    }
  }

  safeRelease(renderTargetTexture);
  return resultRTV;
}

void
Dx11GraphicsAPI::setRenderTargetView(WeakPtr<RenderTargetView>renderTarget, 
                                     WeakPtr<DepthStencilView>deptStencil) {
  if (m_immediateContext == nullptr) {
    BOW_LOG_ERROR( "Null immediate context");
    return;
  }

  ID3D11RenderTargetView* rtv = nullptr;
  ID3D11DepthStencilView* dsv = nullptr;


  if (!renderTarget.expired()) {
    SPtr<Dx11RenderTargetView>tempRTV =
      std::static_pointer_cast<Dx11RenderTargetView>(renderTarget.lock());

    if (tempRTV && tempRTV->m_renderTargetView) {
      rtv = tempRTV->m_renderTargetView;
    }
  }


  if (!deptStencil.expired()) {
    SPtr<Dx11DepthStencilView>tempDSV =
      std::static_pointer_cast<Dx11DepthStencilView>(deptStencil.lock());

    if (tempDSV && tempDSV->m_depthStencilView) {
      dsv = tempDSV->m_depthStencilView;
    }
  }


  {
    ID3D11ShaderResourceView* nullViews[BUFFER_HIGHER_AVAILABLE_SLOT] = { nullptr };
    m_immediateContext->PSSetShaderResources(0,
                                             BUFFER_HIGHER_AVAILABLE_SLOT,
                                             nullViews);
  }


  m_immediateContext->OMSetRenderTargets(1, &rtv, dsv);
}

void 
Dx11GraphicsAPI::setRenderTargetViews( Vector<WeakPtr<RenderTargetView>>& renderTargets, 
                                      WeakPtr<DepthStencilView> depthStencil) {
  if (m_immediateContext == nullptr) {
    BOW_LOG_ERROR( "Null immediate context");
    return;
  }

  Vector<ID3D11RenderTargetView*>rtvs;
  rtvs.reserve(renderTargets.size());

  for (const auto& weakRTV : renderTargets) {
    if (weakRTV.expired())
      continue;

    auto tempRTV =
      std::static_pointer_cast<Dx11RenderTargetView>(weakRTV.lock());
    if (tempRTV && tempRTV->m_renderTargetView) {
      rtvs.push_back(tempRTV->m_renderTargetView);
    }
  }

  ID3D11DepthStencilView* dsv = nullptr;
  if (!depthStencil.expired()) {
    auto tempDSV =
      std::static_pointer_cast<Dx11DepthStencilView>(depthStencil.lock());
    if (tempDSV && tempDSV->m_depthStencilView) {
      dsv = tempDSV->m_depthStencilView;
    }
  }

    ID3D11ShaderResourceView* nullViews[BUFFER_HIGHER_AVAILABLE_SLOT] = { nullptr };
    m_immediateContext->PSSetShaderResources(0,
                                             BUFFER_HIGHER_AVAILABLE_SLOT,
                                             nullViews);

  ID3D11RenderTargetView** rtvsPtr = rtvs.empty() ? nullptr : rtvs.data();
  uint32 numRTVs = static_cast<UINT>(rtvs.size());
  m_immediateContext->OMSetRenderTargets(numRTVs,
                                         rtvsPtr,
                                         dsv);
}

void
Dx11GraphicsAPI::clearRenderTargetView(WeakPtr<RenderTargetView>renderTarget,
                                       float color[4]) {

  if (renderTarget.expired() || m_immediateContext == nullptr) {
    BOW_LOG_ERROR("Expired RenderTargetView or null context");
    return;
  }



  SPtr<Dx11RenderTargetView>tempRTV = 
    std::static_pointer_cast<Dx11RenderTargetView>(renderTarget.lock());

  if (tempRTV && tempRTV->m_renderTargetView) {
    m_immediateContext->ClearRenderTargetView(tempRTV->m_renderTargetView, color);
  }
}

void Dx11GraphicsAPI::clearDepthStencilView(WeakPtr<DepthStencilView>depthStencil,
                                            CLEAR_FLAGS::E flag,
                                            float depth,
                                            uint8 stencil) {

  if (depthStencil.expired() || m_immediateContext == nullptr) {
    BOW_LOG_ERROR("Expired Depth Stencil View");
    return;
  }

  SPtr<Dx11DepthStencilView>tempDS =
    std::static_pointer_cast<Dx11DepthStencilView>(depthStencil.lock());

  if (tempDS && m_immediateContext) {
    uint32  Dx11flag = Dx11DepthStencilView::getClearFlagsDx11(flag);

    m_immediateContext->ClearDepthStencilView(tempDS->m_depthStencilView,
                                              Dx11flag,
                                              depth,
                                              stencil);
  }
}

SPtr<SamplerState>Dx11GraphicsAPI::createSamplerState() {
  if (m_device == nullptr) {
    return nullptr;
  }

  auto samplerState = MakeShared<Dx11SamplerState>();

  D3D11_SAMPLER_DESC sampDesc = {};
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;


  ID3D11SamplerState* rawSampler = nullptr;
  HRESULT hr = m_device->CreateSamplerState(&sampDesc, &rawSampler);
  if (SUCCEEDED(hr)) {
    samplerState->samplerState = rawSampler;

    return samplerState;
  }

  return nullptr;
}

void Dx11GraphicsAPI::setSamplerState(uint32 slot,WeakPtr<SamplerState>sampler) {
  if (m_immediateContext == nullptr || sampler.expired()) {
    return;
  }

  auto dx11Sampler = std::static_pointer_cast<Dx11SamplerState>(sampler.lock());

  if (dx11Sampler && dx11Sampler->samplerState) {
    m_immediateContext->PSSetSamplers(slot,
                                      1,
                                      &dx11Sampler->samplerState);
  }

}

SPtr<DepthStencilView>
Dx11GraphicsAPI::createShadowMap(uint32 width, uint32 height) {
  if (m_device == nullptr || width == 0 || height == 0) {
    return nullptr;
  }

  D3D11_TEXTURE2D_DESC desc = {};
  desc.Width = width;
  desc.Height = height;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_R32_TYPELESS;
  desc.SampleDesc.Count = 1;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  ID3D11Texture2D* tex = nullptr;
  ID3D11DepthStencilView* dsv = nullptr;

  if (SUCCEEDED(m_device->CreateTexture2D(&desc, nullptr, &tex))) {
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Texture2D.MipSlice = 0;

    if (SUCCEEDED(m_device->CreateDepthStencilView(tex, &dsvDesc, &dsv))) {

      D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};  // Shader resource view
      srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
      srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
      srvDesc.Texture2D.MostDetailedMip = 0;
      srvDesc.Texture2D.MipLevels = 1;

      ID3D11ShaderResourceView* srv = nullptr;

      if (SUCCEEDED(m_device->CreateShaderResourceView(tex, &srvDesc, &srv))) {

        auto result = MakeShared<Dx11DepthStencilView>();
        result->m_depthTexture = tex;
        result->m_depthStencilView = dsv;
        result->m_shadowSRV = srv;

        return result;
      }
    }
  }
  safeRelease(dsv);
  safeRelease(tex);
  return nullptr;
}

bool Dx11GraphicsAPI::readShadowMap(WeakPtr<DepthStencilView>shadowDepth, 
                                    Vector<float>& outDepth) {

  if (shadowDepth.expired() || m_device == nullptr ||
      m_immediateContext == nullptr) {
    return false;
  }

  auto depthStencilView = 
    std::static_pointer_cast<Dx11DepthStencilView>(shadowDepth.lock());

  if (!depthStencilView || depthStencilView->m_depthTexture == nullptr) {
    return false;
  }

  D3D11_TEXTURE2D_DESC desc = {};
  depthStencilView->m_depthTexture->GetDesc(&desc);


  D3D11_TEXTURE2D_DESC stagingDesc = {};
  stagingDesc.Width = desc.Width;
  stagingDesc.Height = desc.Height;
  stagingDesc.MipLevels = 1;
  stagingDesc.ArraySize = 1;
  stagingDesc.Format = DXGI_FORMAT_R32_FLOAT;
  stagingDesc.SampleDesc.Count = 1;
  stagingDesc.Usage = D3D11_USAGE_STAGING;
  stagingDesc.BindFlags = 0;
  stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
  stagingDesc.MiscFlags = 0;

  ID3D11Texture2D* stagingTex = nullptr;
  if (SUCCEEDED(m_device->CreateTexture2D(&stagingDesc,
                                          nullptr,&stagingTex))) {

    m_immediateContext->CopyResource(stagingTex,
                                     depthStencilView->m_depthTexture);

    D3D11_MAPPED_SUBRESOURCE mapped = {};

    if (SUCCEEDED(m_immediateContext->Map(stagingTex, 0,
                                          D3D11_MAP_READ, 0, &mapped))) {

      outDepth.resize(desc.Width * desc.Height);

      const uint8* rowPtr = reinterpret_cast<const uint8*>(mapped.pData);
      for (uint32 y = 0; y < desc.Height; ++y) {
        const float* src = reinterpret_cast<const float*>(rowPtr);
        for (uint32 x = 0; x < desc.Width; ++x) {
          outDepth[y * desc.Width + x] = src[x];
        }
        rowPtr += mapped.RowPitch;
      }

      m_immediateContext->Unmap(stagingTex, 0);
      safeRelease(stagingTex);
      return true;
    }
  }
  safeRelease(stagingTex);
  return false;
}

void 
Dx11GraphicsAPI::setShadowMap(uint32 slot, WeakPtr<Texture2D>_mapTexture) {

  if (m_immediateContext == nullptr) {
    return;
  }

  if (_mapTexture.expired()) {
    ID3D11ShaderResourceView* nullViews[1] = { nullptr };
    m_immediateContext->PSSetShaderResources(slot, 1, nullViews);
    return;
  }

  auto Texture = std::static_pointer_cast<Dx11Texture2D>(_mapTexture.lock());
  if (Texture && Texture->textureView) {
    m_immediateContext->PSSetShaderResources(slot, 1, &Texture->textureView);
  }
}

bool 
Dx11GraphicsAPI::isOccluded(WeakPtr<DepthStencilView>shadowDepth, 
                            const Vector3& worldPos, const Matrix4& shadowView, 
                            const Matrix4 shadowProjection, float bias) {
  
  if (shadowDepth.expired() || m_device == nullptr ||
      m_immediateContext == nullptr) {
    return false;
  }

  auto dxDSV = 
    std::static_pointer_cast<Dx11DepthStencilView>(shadowDepth.lock());

  if (!dxDSV || dxDSV->m_depthTexture == nullptr) {
    return false;
  }

  Vector<float>depthData;
  if (!readShadowMap(shadowDepth, depthData)) {
    return false;
  }

  D3D11_TEXTURE2D_DESC desc = {};
  dxDSV->m_depthTexture->GetDesc(&desc);
  uint32 width = desc.Width;
  uint32 height = desc.Height;
  if (width == 0 || height == 0 || depthData.size() < (SIZE_T)width * (SIZE_T)height) {
    return false;
  }

  Matrix4 vp = shadowProjection * shadowView;
  Vector4 clip = vp.transformPosition(worldPos);

  if (clip.w == 0.0f) {
    return false;
  }

  float invW = 1.0f / clip.w;
  float ndcX = clip.x * invW;
  float ndcY = clip.y * invW;
  float ndcZ = clip.z * invW;

  float u = ndcX * 0.5f + 0.5f;
  float v = ndcY * 0.5f + 0.5f;
  float depth = ndcZ * 0.5f + 0.5f;


  if (u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f) {
    return false;
  }

  int tx = static_cast<int>(Math::clamp(u * static_cast<float>(width), 0.0f, 
                             static_cast<float>(width - 1)));

  int ty = static_cast<int>(Math::clamp(v * static_cast<float>(height), 0.0f,
                                       static_cast<float>(height - 1)));

  float stored = depthData[ty * width + tx];

  return (depth - bias) > stored;
}

void 
Dx11GraphicsAPI::setShadowMapFromDepthView(uint32 slot,
                                           WeakPtr<DepthStencilView>shadowDepth) {

  if (m_immediateContext == nullptr) {
    return;
  }

  if (shadowDepth.expired()) {
    setShadowMap(slot, SPtr<Texture2D>());
    return;
  }

  auto depthStencilView = 
    std::static_pointer_cast<Dx11DepthStencilView>(shadowDepth.lock());

  if (!depthStencilView || depthStencilView->m_shadowSRV == nullptr) {
    setShadowMap(slot, SPtr<Texture2D>());
    return;
  }

  auto wrapper = MakeShared<Dx11Texture2D>();
  wrapper->texture = nullptr;
  wrapper->textureView = depthStencilView->m_shadowSRV;
  depthStencilView->m_shadowSRV->AddRef();

  SPtr<Texture2D>tex = StaticPointerCast<Texture2D>(wrapper);
  setShadowMap(slot, tex);
}


SPtr <Texture2D>
Dx11GraphicsAPI::createTexture2DWithImageData(const Vector<uint8>& imgData,
                                              int32 witdh,int32 height) {
  auto texture = MakeShared<Dx11Texture2D>();

  if (imgData.empty() || witdh <= 0 || height <= 0 || m_device == nullptr) {
    return nullptr;
  }

  D3D11_TEXTURE2D_DESC texDesc = {};
  texDesc.Width = static_cast<UINT>(witdh);
  texDesc.Height = static_cast<UINT>(height);
  texDesc.MipLevels = 1;
  texDesc.ArraySize = 1;
  texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  texDesc.SampleDesc.Count = 1;
  texDesc.SampleDesc.Quality = 0;
  texDesc.Usage = D3D11_USAGE_DEFAULT;
  texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texDesc.CPUAccessFlags = 0;
  texDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA subData = {};
  subData.pSysMem = imgData.data();
  subData.SysMemPitch = static_cast<UINT>(witdh * 4);
  subData.SysMemSlicePitch = 0;

  if (SUCCEEDED(m_device->CreateTexture2D(&texDesc,
                                          &subData,
                                          &texture->texture))) {
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = texDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;

    if (SUCCEEDED(m_device->CreateShaderResourceView(texture->texture,
                                                     &srvDesc,
                                                     &texture->textureView))) {
      return texture;
    }
  }
  BOW_LOG_ERROR("Error loading texture to dx11.");
  return nullptr;
}


void
Dx11GraphicsAPI::setTexture2D(uint32 slot, WeakPtr<Texture2D>texture) {
  if (m_immediateContext == nullptr)
    return;


  if (texture.expired()) {
    ID3D11ShaderResourceView* nullView[1] = { nullptr };
    m_immediateContext->PSSetShaderResources(slot, 1, nullView);
    return;
  }

  auto base = texture.lock();


  if (auto dxTex = std::static_pointer_cast<Dx11Texture2D>(base)) {
    if (dxTex->textureView) {
      m_immediateContext->PSSetShaderResources(slot, 1, &dxTex->textureView);
      return;
    }
  }


  if (auto dxRTV = std::static_pointer_cast<Dx11RenderTargetView>(base)) {
    if (dxRTV->m_resourceView) {
      m_immediateContext->PSSetShaderResources(slot, 1, &dxRTV->m_resourceView);
      return;
    }
  }


  {
    ID3D11ShaderResourceView* nullView[1] = { nullptr };
    m_immediateContext->PSSetShaderResources(slot, 1, nullView);
  }
}


}/// name space bowEngineSDK
