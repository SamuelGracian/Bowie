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
  createInputLayout( const ID3D10ShaderReflection* _reflection) const;

  /*
  * @brief
  * @param HWND, uin32, uint32, GAPI_FORMAT, ID3D11Device
  *  Window handler, width, height, format, reference to thr device.
  * @return IDXGISwapChain
  *  Returns a pointer of type swap chain.
  */
  IDXGISwapChain*
  createSwapChain(HWND _windowHandler, uint32 _width, uint32 _height,
                  GAPI_FORMAT::E _format, ID3D11Device& m_device) const;

  /*
  * @brief
  * create back buffer for the render target.
  * @param IDXGISwapChain*
  * @return ID3D11RendertTargetView*
  */
  ID3D11RenderTargetView*
  createbackBufferRT(IDXGISwapChain* _swapChain)const;

};
}/// namespace bowEngineSDK
