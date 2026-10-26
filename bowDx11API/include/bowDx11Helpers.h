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




};
}/// namespace bowEngineSDK
