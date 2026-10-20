#pragma once

#include "bowDx11Requisites.h"
#include "bowSTDheaders.h"

namespace bowEngineSDK
{
class Dx11Helpers
{
public:

  /*
  * @brief
  *  Gets the according DXGI format to the GAPI_FORMAT
  * @param GAPI_FORMAT
  * @return
  *  DXGI_FORMAT
  */
  DXGI_FORMAT
  getDx11Format(GAPI_FORMAT::E _format) const;

  /*
  */
  uint32
  getDx11BindFlags(const uint32 _bindFlag) const;

  const char*
  getShaderModel(SHADER_TYPE::E _shaderType, uint32 _shaderModel) const;

  D3D11_CULL_MODE
  getCullMode(CULL_MODE::E _cullMode) const;

  D3D11_FILL_MODE
  getFillMode(FILL_MODE::E _fillMode) const;


  Vector<D3D11_INPUT_ELEMENT_DESC>
  createInputLayout( const ID3D10ShaderReflection* _reflection) const;

};
}/// namespace bowEngineSDK
