#include "bowDx11Helpers.h"

namespace bowEngineSDK
{

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
Dx11Helpers::createInputLayout( ID3D11ShaderReflection* _reflection) const {
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

/// * or &


}/// namespace bowEngineSDK
