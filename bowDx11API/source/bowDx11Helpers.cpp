#include "bowDx11Helpers.h"

namespace bowEngineSDK
{
DXGI_FORMAT
Dx11Helpers::getDx11Format(GAPI_FORMAT::E _format) const {
  switch (_format) {
  default:
    return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
    break;

  case GAPI_FORMAT::FORMAT_D24_UNORM_S8_UINT:
    return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
    break;

  case GAPI_FORMAT::FORMAT_R8G8B8A8_UNORM:
    return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

  case GAPI_FORMAT::FORMAT_R32_FLOAT:
    return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
  }
}


uint32
Dx11Helpers::getDx11BindFlags(const uint32 _bindFlag) const {
  uint32 ResultFlags = 0;

  if ((_bindFlag & GAPI_BIND_FLAGS::BIND_CONSTANT_BUFFER) != 0) {
    ResultFlags += D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
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
Dx11Helpers::getShaderModel(SHADER_TYPE::E _shaderType, uint32 _shaderModel) const {
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


D3D11_CULL_MODE
Dx11Helpers::getCullMode(CULL_MODE::E _cullMode) const {
  switch (_cullMode) 
  {
  default:
    return D3D11_CULL_MODE::D3D11_CULL_NONE;
    break;

  case CULL_MODE::CULL_BACK:
    return D3D11_CULL_MODE::D3D11_CULL_BACK;
    break;

  case CULL_MODE::CULL_FRONT:
    return D3D11_CULL_MODE::D3D11_CULL_FRONT;
    break;
  }
}

D3D11_FILL_MODE
Dx11Helpers::getFillMode(FILL_MODE::E _fillMode) const {
  switch (_fillMode) {
  default:
    return D3D11_FILL_MODE::D3D11_FILL_SOLID;
    break;

  case FILL_MODE::FILL_WIREFRAME:
    return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    break;
  }
}

Vector<D3D11_INPUT_ELEMENT_DESC>
Dx11Helpers::createInputLayout(const ID3D10ShaderReflection* _reflection) const {
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

IDXGISwapChain*
Dx11Helpers::createSwapChain(HWND _windowHandler, uint32 _width, uint32 _height,
                             GAPI_FORMAT::E _format, ID3D11Device& m_device) const {
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

          sd.Width = _width;
          sd.Height = _height;
          sd.Format = getDx11Format(_format);
          sd.SampleDesc.Count = 1;
          sd.SampleDesc.Quality = 0;
          sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
          sd.BufferCount = 2;
          sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
          sd.Scaling = DXGI_SCALING_NONE;
          sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

          hr = dxgiFactory2->CreateSwapChainForHwnd(m_device, _windowHandler, 
                                                    &sd, nullptr, nullptr, 
                                                    &swapChain1);

          if (SUCCEEDED(hr)) {
            hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain), 
                                            reinterpret_cast<void**>(&ResultSwapChain));
          }
        }
        else {
          DXGI_SWAP_CHAIN_DESC sd = {};

          sd.BufferCount = 1;
          sd.BufferDesc.Width = _width;
          sd.BufferDesc.Height = _height;
          sd.BufferDesc.Format = getDx11Format(_format);
          sd.BufferDesc.RefreshRate.Numerator = 60;
          sd.BufferDesc.RefreshRate.Denominator = 1;
          sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
          sd.OutputWindow = _windowHandler;
          sd.SampleDesc.Count = 1;
          sd.SampleDesc.Quality = 0;
          sd.Windowed = TRUE;

          hr = dxgiFactory1->CreateSwapChain(m_device, &sd, &ResultSwapChain);
        }

        dxgiFactory1->MakeWindowAssociation(_windowHandler, DXGI_MWA_NO_ALT_ENTER);
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
Dx11Helpers::createbackBufferRT(IDXGISwapChain& _swapChain, 
                                ID3D11Device& m_device) const {

  ID3D11Texture2D* resultTextureRT = nullptr;

  ID3D11RenderTargetView* resultRT = nullptr;

  if (_swapChain != nullptr && m_device != nullptr) {

    if (SUCCEEDED(_swapChain.GetBuffer(0, __uuidof(ID3D11Texture2D),
                                       reinterpret_cast<void**>(&resultTextureRT)))) {

      m_device.CreateRenderTargetView(resultTextureRT, nullptr, &resultRT);
    }
  }
  safeRelease(resultTextureRT);

  return resultRT;
}

}/// namespace bowEngineSDK
