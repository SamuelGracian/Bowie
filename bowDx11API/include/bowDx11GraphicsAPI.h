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
  createConstBuffer(const uint32 byteWitdh,
                    const uint32 slot) override;

  /*
  * @brief
  * Creates and index buffer and sets an initial data.
  * @param uint32, void*
  * @return sharedPtr<IndexBuffer>.
  */
  virtual SPtr<Indexbuffer>
  createIndexBuffer(const uint32 _byteWidth, void* data) override;

  /*
  * @brief
  *  Creates a vertex buffer.
  * @param uint32, const void*
  * @return shared ptr <VertexBuffer>
  */
  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 _byteWidth, const void* _vertices) override;

  /*
  * @brief
  *  Sets the constant buffer with a given data.
  * @param weaKPtr<ConstBuffer>, void*
  * @return void.
  */
  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer, void* _data) override;

  /*
  * @brief
  *  Gets a bowie index buffer, internali turns it into a Dx11 buffer and sets it.
  * @param weakPtr <IndexBuffer>
  * @return void
  */
  virtual void
  setIndexBuffer(WeakPtr<Indexbuffer> buffer) override;

  /*
  * @brief
  *  Updates the info in the given const buffer.
  * @param weakPtr <constBUffer>, const uint32 byteWidth.
  * @return void
  */
  virtual void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWitdth,
                    void* data = nullptr) override;

  /*
  * @brief
  *  Creates a topology.
  *  Sets as default the topology as a Triangle list.
  * @param TOPOLOGY::TYPE
  * @return SharedPtr Topology
  */
  virtual SPtr<Topology>
  createTopology(Topology::Type _type) override;

  virtual void
  setTopology(WeakPtr<Topology> _topology) override;


  virtual SPtr<DepthStencilView>
  createDepthStencil(uint32 _width, uint32 _height,
                     const GAPI_FORMAT::E _format) override;


  virtual SPtr <ViewPort>
  createViewPort(float _width, float height, 
                 const GAPI_FORMAT::E _format)override;


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

  /*
  * @brief
  *  Creates a texture of Dx11 type.
  * @param uint32 width, uint32 hieght, const GAPI_FORMAT, uint32 bindflag
  * @return ID3D11Texture2D*
  */
  ID3D11Texture2D*
  createTexture2DInternal(uint32 _width, uint32 _height,
                          const GAPI_FORMAT::E _format, uint32 _bindFlags);

  uint32
  getDx11BindFlagsInternal(const uint32 _bindFlag) const;


private:
  ID3D11Device* m_device = nullptr;
  ID3D11DeviceContext* m_immediateContext = nullptr;

};
}/// namespace GraphicsAPI
