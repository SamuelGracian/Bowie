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

   virtual bool
   cleanUpResources() override;

   virtual SPtr<SwapChain>
   createSwapChain(WeakPtr<DisplaySurface> handle,
                     GAPI_FORMAT::K) override;
   
   virtual SPtr<ConstBuffer>
   createConstBuffer(const uint32 byteWitdh = 0,
                     const uint32 slot = 0, void* data = nullptr) override;

   virtual SPtr<Indexbuffer>
   createIndexBuffer(WeakPtr<Indexbuffer> buffer) override;

   virtual SPtr<VertexBuffer>
   createVertexBuffer(WeakPtr<VertexBuffer> buffer ) override;

   virtual void
   setConstBuffer(WeakPtr<ConstBuffer> buffer) override;

   virtual void
   setIndexBuffer(WeakPtr<Indexbuffer> buffer) override;

   virtual void
   updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWitdth,
                     void* data = nullptr) override;

   /*  INTERNAL FUNCTIONS  */
   IDXGISwapChain*
   createSwapChainInternal(HWND hwnd, uint32_t width,
                           uint32_t height,
                           GAPI_FORMAT::K format);


 private:
   ID3D11Device* m_device = nullptr;
   ID3D11DeviceContext* m_immediateContext = nullptr;

};
}/// namespace GraphicsAPI
