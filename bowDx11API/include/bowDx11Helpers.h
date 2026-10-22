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
  * @param uint32
  * @return uint32
  */
  uint32
  getDx11BindFlags(const uint32 _bindFlag) const;

  /*
  * @brief
  * @param SHADER_TYPE, uint32
  *   shader type and shader model.
  * @return const char*
  */
  const char*
  getShaderModel(SHADER_TYPE::E _shaderType, uint32 _shaderModel) const;

  /*
  * @brief
  *  recieves a cull mode of type bowie and returns the Dx11 version of it.
  * @param CULL_MODE
  * @reutrn D3D11_CULL_MODE
  */
  D3D11_CULL_MODE
  getCullMode(CULL_MODE::E _cullMode) const;

  /*
  * @brief
  *  Recieves a fill mode of type bowie and returns the Dx11 version fo it.
  * @param FILL_MODE
  * @return D3D11_FILL_MODE
  */
  D3D11_FILL_MODE
  getFillMode(FILL_MODE::E _fillMode) const;

  /*
  * @brief
  *  Creates an input layout.
  * @param ID3D10ShaderReflection
  * @return   Vector<D3D11_INPUT_ELEMENT_DESC>
  */
  Vector<D3D11_INPUT_ELEMENT_DESC>
  createInputLayout(ID3D11ShaderReflection* _reflection) const;

};
}/// namespace bowEngineSDK
