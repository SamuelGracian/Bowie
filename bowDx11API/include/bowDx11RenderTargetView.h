#pragma once 

#include "bowRenderTargetView.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11RenderTargetView : public RenderTargetView
{
public:
  
  /*
  * @brief
  *  Default constructor
  */
  Dx11RenderTargetView()
    :m_renderTargetView(nullptr), m_resourceView(nullptr)
  {}

  /*
  * @brief
  *  Default destructor
  */
  ~Dx11RenderTargetView() = default;

 protected:
   ID3D11RenderTargetView* m_renderTargetView;
   ID3D11ShaderResourceView* m_resourceView;

};

}/// namespace bowEngineSDK
