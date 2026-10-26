#include "bowDx11GraphicsAPI.h"

#include <iostream>
#include <windows.h>
#include <d3dcompiler.h>
#include <limits>
#include <d3d11shader.h>

#include "bowDx11ConstBuffer.h"
#include "bowDx11IndexBuffer.h"
#include "bowDx11VertexBuffer.h"
#include "bowDx11SwapChain.h"
#include "bowDx11Helpers.h"
#include "bowDx11Topology.h"
#include "bowDx11DepthStencilView.h"
#include "bowDx11Helpers.h"
#include "bowDx11VertexShader.h"
#include "bowDx11PixelShader.h"

namespace bowEngineSDK
{
/*****************************************************/
/*  INTERNAL FUNCTIONS/ HELPERS  */
/*****************************************************/

DXGI_FORMAT
Dx11GraphicsAPI::getDx11FormatInternal(GAPI_FORMAT::E _format) const {
  switch (_format) {
  default:
    return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
    break;

  case GAPI_FORMAT::FORMAT_D24_UNORM_S8_UINT:
    return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
    break;

  case GAPI_FORMAT::FORMAT_R8G8B8A8_UNKNOWN:
    return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

  case GAPI_FORMAT::FORMAT_R32_FLOAT:
    return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
  }
}


uint32
Dx11GraphicsAPI::getDx11BindFlagsInternal(const uint32 _bindFlag) const {
  uint32 ResultFlags = 0;

  if ((_bindFlag & GAPI_BIND_FLAGS::BIND_CONSTANT_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_CONSTANT_BUFFER;
  }

  if ((_bindFlag & GAPI_BIND_FLAGS::BIND_INDEX_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_INDEX_BUFFER;
  }

  if ((_bindFlag & GAPI_BIND_FLAGS::BIND_VERTEX_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_VERTEX_BUFFER;
  }

  if ((_bindFlag & GAPI_BIND_FLAGS::DEPTH_STENCIL) != 0) {
    ResultFlags += D3D11_BIND_DEPTH_STENCIL;
  }

  if ((_bindFlag & GAPI_BIND_FLAGS::RENDER_TARGET) != 0) {
    ResultFlags += D3D11_BIND_RENDER_TARGET;
  }

  if ((_bindFlag & GAPI_BIND_FLAGS::SHADER_RESOURCE) != 0) {
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
  case SHADER_TYPE::E::VERTEX_SHADER:
    ResultShader = "vs_" + modelVersion;
    break;

  case SHADER_TYPE::E::PIXEL_SHADER:
    ResultShader = "ps_" + modelVersion;
    break;

  default:
    ResultShader = "vs_4_0";
    break;
  }

  return ResultShader.c_str();
}

IDXGISwapChain* 
Dx11GraphicsAPI::createSwapChainInternal(HWND hwnd, uint32 width,
                                         uint32 height, GAPI_FORMAT::E format) {
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
          sd.Format = getDx11FormatInternal(format);
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

ID3D11RenderTargetView*
Dx11GraphicsAPI::createBackBufferRTInternal(IDXGISwapChain* _swapChain) {

  ID3D11Texture2D* resultTextureRT = nullptr;

  ID3D11RenderTargetView* resultRT = nullptr;

  if (_swapChain != nullptr && m_device != nullptr) {

    if (SUCCEEDED(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                        reinterpret_cast<void**>(&resultTextureRT)))) {

      m_device->CreateRenderTargetView(resultTextureRT, nullptr, &resultRT);
    }
  }
  safeRelease(resultTextureRT);

  return resultRT;
}

ID3D11Texture2D*
Dx11GraphicsAPI::createTexture2DInternal(uint32 _width, uint32 _height,
                                         const GAPI_FORMAT::E _format,
                                         uint32 _bindFlags) {
  
  ID3D11Texture2D* resultTexture = nullptr;

  if (_width != 0 && _height != 0
      && _format != GAPI_FORMAT::FORMAT_R8G8B8A8_UNKNOWN
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
    m_device->CreateTexture2D(&descTexture, nullptr, &resultTexture);
  }
  return resultTexture;
}

ID3DBlob*
Dx11GraphicsAPI::compileShaderInternal(const String& _shaderCode,
                                       const String& _entryPoint,
                                       Vector<String> _defines,
                                       SHADER_TYPE::E _shaderType) {
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

    for (auto& macro : _defines) {
      finalShaderCore += (macro = '\n');
    }

    finalShaderCore += _shaderCode;

    if (FAILED(D3DCompile(finalShaderCore.c_str(), finalShaderCore.length(),
                          nullptr, nullptr, nullptr,_entryPoint.c_str(),
                          getShaderModelInternal(_shaderType, m_shaderModel), 
                          dwShaderFlag, 0, &binaryBlob, &errorBlob))) {
      if (errorBlob) {
        std::cout << "Shader compilation error" <<
          reinterpret_cast<const char*>(errorBlob->GetBufferPointer()) 
          << std::endl;
      }
    }
  }

  safeRelease(errorBlob);
  return binaryBlob;
}

Vector<D3D11_INPUT_ELEMENT_DESC>
Dx11GraphicsAPI::createInputLayoutInternal(ID3D11ShaderReflection* _reflection) 
const {
  Vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

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
      if (paramDesc.Mask == 1) componentCount = 1;
      else if (paramDesc.Mask <= 3) componentCount = 2;
      else if (paramDesc.Mask <= 7) componentCount = 3;
      else if (paramDesc.Mask <= 15) componentCount = 4;

      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        if (componentCount == 1) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        else if (componentCount == 2) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        else if (componentCount == 3) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        else if (componentCount == 4) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        if (componentCount == 1) elementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if (componentCount == 2) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if (componentCount == 3) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if (componentCount == 4) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
        if (componentCount == 1) elementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if (componentCount == 2) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if (componentCount == 3) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if (componentCount == 4) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
      }

      inputLayoutDesc.push_back(elementDesc);
    }
  }
  return inputLayoutDesc;
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

void
Dx11GraphicsAPI::draw(uint32 _vertexCount, uint32 _startVertexLocation) {
  if (m_immediateContext) {
    m_immediateContext->DrawIndexed(_vertexCount, _startVertexLocation, 0);
  }
}

void
Dx11GraphicsAPI::cleanUpResources(){}

SPtr<SwapChain>
Dx11GraphicsAPI::createSwapChain(WeakPtr<DisplaySurface> _windowHandler,
                                 GAPI_FORMAT::E _format) {
  SPtr<Dx11SwapChain> SChain = nullptr;

  if (_windowHandler.expired()) {
    std::cout << "Handle window expired" << std::endl;
    return SChain;
  }

  std::shared_ptr<DisplaySurface> tempSurface = _windowHandler.lock();

  if (auto* ResultSwapChain = createSwapChainInternal(
                                  reinterpret_cast<HWND> (tempSurface->getHandle()),
                                  tempSurface->getClientWidth(), 
                                  tempSurface->getClientHeight(),
                                  _format)) {
    if (auto* ResultRT = createBackBufferRTInternal(ResultSwapChain)) {
      SChain = std::make_shared<Dx11SwapChain>();

      SChain->m_backBufferRT = ResultRT;

      SChain->m_swapChain = ResultSwapChain;
    }
  }
  return SChain;
}

SPtr<ConstBuffer>
Dx11GraphicsAPI::createConstBuffer(const uint32 _byteWidth,
                             const uint32 slot) {
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
    auto buffer = std::make_shared<Dx11ConstBuffer>();
    buffer->m_buffer = Rawbuffer;
    buffer->setByteWidth(_byteWidth);
    buffer->setSlot(slot);

    //ASSIGN_DEBUG_NAME(buffer.get(), Rawbuffer);
    return buffer;
  }
  return nullptr;
}

SPtr<Indexbuffer>
Dx11GraphicsAPI::createIndexBuffer(const uint32 _byteWidth, void* _data) {
  BOW_ASSERT(_byteWidth != 0);
  D3D11_BUFFER_DESC bd = {};
  ID3D11Buffer* Rawbuffer = nullptr;
  D3D11_SUBRESOURCE_DATA InitData = {};
  auto ResultBuffer = std::make_shared<Dx11IndexBuffer>();

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = _byteWidth;
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  InitData.pSysMem = _data;

  if (SUCCEEDED(m_device->CreateBuffer(&bd, &InitData, &Rawbuffer))) {
    ResultBuffer->m_buffer = Rawbuffer;
  }

  return ResultBuffer;
}

SPtr<VertexBuffer>
Dx11GraphicsAPI::createVertexBuffer(const uint32 _byteWidth,
                                    const void* _vertices) {
  ID3D11Buffer* Rawbuffer = nullptr;
  std::shared_ptr<Dx11VertexBuffer> ResultBuffer;

  D3D11_BUFFER_DESC bd = {};
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = _byteWidth;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA InitData = {};
  InitData.pSysMem = _vertices;

  if (SUCCEEDED(m_device->CreateBuffer(&bd, &InitData, &Rawbuffer))) {
    ResultBuffer = std::make_shared<Dx11VertexBuffer>();
    ResultBuffer->m_buffer = Rawbuffer;
  }
  return ResultBuffer;
}

void
Dx11GraphicsAPI::setConstBuffer(WeakPtr<ConstBuffer> buffer, void* _data) {
  if (m_immediateContext == nullptr || buffer.expired()) {
    return;
  }
  auto pbuffer = std::static_pointer_cast<Dx11ConstBuffer>(buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->getSlot() 
      >= BUFFER_HIGHER_AVAILABLE_SLOT) {
    return;
  }

  m_immediateContext->VSSetConstantBuffers(pbuffer->getSlot(), 1, &pbuffer->m_buffer);
  m_immediateContext->PSSetConstantBuffers(pbuffer->getSlot(), 1, &pbuffer->m_buffer);

  //Sets the data on the buffer
  m_immediateContext->UpdateSubresource(pbuffer->m_buffer, 0, nullptr, _data, 0, 0);
}

void
Dx11GraphicsAPI::setVertexBuffer(WeakPtr<VertexBuffer> _buffer, uint32 _stride,
                                 uint32 _offset) {
  if (!_buffer.expired() || m_immediateContext != nullptr) {
    auto pBuffer = std::static_pointer_cast<Dx11VertexBuffer>(_buffer.lock());

    if (pBuffer && pBuffer->m_buffer) {
      m_immediateContext->IASetVertexBuffers(0, 1, &pBuffer->m_buffer,
                                             &_stride, &_offset);
    }
  }
  return;
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
Dx11GraphicsAPI::updateConstBuffer(WeakPtr<ConstBuffer> _buffer,
                             const uint32 _byteWidth, void* _data) {
  if (m_immediateContext == nullptr || _buffer.expired() || _data == nullptr) {
    return;
  }
  auto pbuffer = std::static_pointer_cast <Dx11ConstBuffer> (_buffer.lock());

  if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->GetByteWidth() != _byteWidth) {
    return;
  }

  m_immediateContext->UpdateSubresource(pbuffer->m_buffer, 0, nullptr, _data, 0, 0);
}

SPtr<Topology>
Dx11GraphicsAPI::createTopology(Topology::Type _type) {
  auto topo = std::make_shared<Dx11Topology>();

  topo->setType(_type);

  switch (_type) {
  case bowEngineSDK::Topology::TriangleList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;

  case bowEngineSDK::Topology::TriangleStrip:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    break;

  case bowEngineSDK::Topology::LineList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    break;

  case bowEngineSDK::Topology::PointList:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    break;

  default:
    topo->dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    break;
  }

  return topo;
}

void
Dx11GraphicsAPI::setTopology(WeakPtr<Topology> _topology){
  if (m_immediateContext == nullptr || _topology.expired()){
    return;
   }

  auto pTopo = std::static_pointer_cast<Dx11Topology>(_topology.lock());
  if (pTopo == nullptr) {
    return;
  }

  m_immediateContext->IASetPrimitiveTopology(pTopo->dx11Topology);
}

SPtr<DepthStencilView>
Dx11GraphicsAPI::createDepthStencil(uint32 _width, uint32 _height,
                                    const GAPI_FORMAT::E _format) {
  
  SPtr<Dx11DepthStencilView> resultDS = nullptr;
  ID3D11DepthStencilView* resultDepthStencilView = nullptr;
  ID3D11Texture2D* depthStencilTexture = nullptr;

  if (m_device != nullptr && _width != 0.0f && _height != 0.0
      && _format != GAPI_FORMAT::FORMAT_R8G8B8A8_UNKNOWN) {

    depthStencilTexture = createTexture2DInternal(_width,
                                                  _height,
                                                  _format,
                                                  GAPI_BIND_FLAGS::DEPTH_STENCIL);

    if (depthStencilTexture != nullptr){
      D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
      descDSV.Format = getDx11FormatInternal(_format);
      descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
      descDSV.Texture2D.MipSlice = 0;

      if (SUCCEEDED(m_device->CreateDepthStencilView(depthStencilTexture,
                                                     &descDSV,
                                                     &resultDepthStencilView))) {
        resultDS = std::make_shared<Dx11DepthStencilView>();
        resultDS->m_depthStencilView = resultDepthStencilView;
      }
    }
  }
  safeRelease(depthStencilTexture);
  return resultDS;
}

SPtr<ViewPort>
Dx11GraphicsAPI::createViewPort() {
  return SPtr<ViewPort> ();
}

SPtr<VertexShader>
bowEngineSDK::Dx11GraphicsAPI::createVertexShader(const String& _shaderCode,
                                                  const String& _entryPoint,
                                                  Vector<String> _defines) {
  ID3DBlob* binaryBlob = nullptr;
  ID3D11ShaderReflection* shaderReflection = nullptr;
  ID3D11VertexShader* resultShader = nullptr;
  ID3D11InputLayout* resultLayout = nullptr;

  binaryBlob = compileShaderInternal(_shaderCode, _entryPoint, _defines,
                                     SHADER_TYPE::VERTEX_SHADER);

  SPtr<Dx11VertexShader> resultVShader = nullptr;

  if (binaryBlob != nullptr && m_device != nullptr) {
    if (SUCCEEDED(D3DReflect(binaryBlob->GetBufferPointer(),
                             binaryBlob->GetBufferSize(),
                             IID_ID3D11ShaderReflection,
                             (void**)&shaderReflection))) {

      const auto desc = createInputLayoutInternal(shaderReflection);

      const UINT numElements = static_cast<UINT>(desc.size());

      if (desc.empty()) {
        if (SUCCEEDED(m_device->CreateVertexShader(binaryBlob->GetBufferPointer(),
                                                   binaryBlob->GetBufferSize(),
                                                   nullptr, &resultShader)) &&
            SUCCEEDED(m_device->CreateInputLayout(desc.data(), numElements, ///  warning C4267: 'argument': conversion from 'size_t' to 'UINT', possible loss of data
                                                  binaryBlob->GetBufferPointer(),
                                                  binaryBlob->GetBufferSize(),
                                                  &resultLayout))) {
          resultVShader = std::make_shared<Dx11VertexShader>();
          resultVShader->m_shader = resultShader;
          resultVShader->m_InputLayout = resultLayout;
        }
      }
    }
  }
  safeRelease(shaderReflection);
  safeRelease(binaryBlob);
  return resultVShader;
}

void
Dx11GraphicsAPI::setVertexShader(WeakPtr<VertexShader> _shader) {
  if (_shader.expired()) {
    return;
  }

  auto resultShader = 
    std::reinterpret_pointer_cast<Dx11VertexShader>(_shader.lock());

  if (resultShader && m_immediateContext) {
    m_immediateContext->IASetInputLayout(resultShader->m_InputLayout);
    m_immediateContext->VSSetShader(resultShader->m_shader, nullptr, 0);
  }
}

SPtr<PixelShader>
Dx11GraphicsAPI::createPixelShader(const String& _shaderCode,
                                   const String& _entryPoint,
                                   Vector<String> _defines) {
  ID3DBlob* binaryBlob = nullptr;
  ID3D11PixelShader* resultShader = nullptr;
  SPtr<Dx11PixelShader> shaderPtr = nullptr;

  binaryBlob = compileShaderInternal(_shaderCode, _entryPoint, _defines,
                                     SHADER_TYPE::PIXEL_SHADER);

  if (binaryBlob == nullptr || m_device == nullptr) {
    std::cout <<
      "createPixelShader function, binary blob = nullptr, or device = nullptr" <<
      std::endl;
    return nullptr;
  }
  
  if (SUCCEEDED(m_device->CreatePixelShader(binaryBlob->GetBufferPointer(),
                                            binaryBlob->GetBufferSize(),
                                            nullptr, &resultShader))) {
    shaderPtr = std::make_shared<Dx11PixelShader>();

    shaderPtr->pixShader = resultShader;
  }
  safeRelease(binaryBlob);
  return shaderPtr;
}

void Dx11GraphicsAPI::setPixelShader(WeakPtr<PixelShader> _shader) {
  if (_shader.expired() || m_immediateContext == nullptr) {
    std::cout <<
      "setPixelShader function" << '/n' << 
      "shader or immmediate contextex = nullptr" << 
      std::endl;
  }
  auto p_Ps = std::reinterpret_pointer_cast<Dx11PixelShader> (_shader.lock());
  m_immediateContext->PSSetShader(p_Ps->pixShader, nullptr, 0);
}


}/// namespace bowEngineSDK
