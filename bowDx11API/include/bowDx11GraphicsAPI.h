#pragma once 

#include "bowGraphicsAPI.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11GraphicsAPI : public GraphicsAPI
{
 public:
  Dx11GraphicsAPI() = default;

  virtual bool
  init(WeakPtr<DisplaySurface> handlewindow) override;

  virtual SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> _windowHandler,
                    GAPI_FORMAT::E _format) override;
  
  /*
  * @brief 
  * Create an empty buffer. It saves info in the update function.
  * @param
  * @return
  */
  virtual SPtr<ConstBuffer>
  createConstBuffer(const uint32 byteWitdh ,
                    const uint32 slot) override;

  virtual SPtr<Indexbuffer>
  createIndexBuffer(const uint32 _byteWidth, void* data) override;

  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 _byteWidth, const void* _vertices) override;

  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer, void* _data) override;

  virtual void
  setIndexBuffer(WeakPtr<Indexbuffer> buffer) override;

  virtual void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWitdth,
                    void* data = nullptr) override;

  /*  INTERNAL FUNCTIONS  */
  
  /*
  * @brief
  * @param HWND, uin32, uint32, GAPI_FORMAT, ID3D11Device
  *  Window handler, width, height, format, reference to thr device.
  * @return IDXGISwapChain
  *  Returns a pointer of type swap chain.
  */
  IDXGISwapChain*
  createSwapChainInternal(HWND hwnd, uint32 width,
                          uint32 height,
                          GAPI_FORMAT::E format);
   
  /* 
  * @brief
  *  Gets the according DXGI format to the GAPI_FORMAT
  * @param GAPI_FORMAT
  * @return
  *  DXGI_FORMAT
  */
  DXGI_FORMAT
  getDx11FormatInternal(GAPI_FORMAT::E _format) const;

  /*
* @brief
* create back buffer for the render target.
* @param IDXGISwapChain*
* @return ID3D11RendertTargetView*
*/
  ID3D11RenderTargetView*
  createBackBufferRTInternal(IDXGISwapChain* _swapChain);


 private:
   ID3D11Device* m_device = nullptr;
   ID3D11DeviceContext* m_immediateContext = nullptr;

};
}/// namespace GraphicsAPI
