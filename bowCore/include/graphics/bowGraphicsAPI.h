#pragma once

/// To do: alphabetical order, comments on functions
#include "bowCoreRequisites.h"
#include "bowMatrix.h"
#include "bowVector3.h"
#include "bowVector4.h"
#include "bowWindow.h"
#include "bowRenderTargetView.h"
#include "bowConstBuffer.h"
#include "bowIndexBuffer.h"
#include "bowVertexBuffer.h"
#include "bowGraphicsGenerals.h"

namespace bowEngineSDK
{

struct SimpleVertex
{
  Vector4 position;
  Vector4 normals;
  Vector4 tangent;
  Vector4 binormals;
  Vector4 texture;

  /*
  * @brief
  *  Constructor for simple vertex.???
  */
  SimpleVertex(
    Vector4& pos,
    Vector4& normal,
    Vector4& tan ,
    Vector4& binormal,
    Vector4& tex )
    : position(pos), normals(normal), tangent(tan), binormals(binormal),
    texture(tex) {}
};/// Simple vertex struct

class BOW_CORE_EXPORT GraphicsAPI 
{
public:

  GraphicsAPI():
   m_shaderModel(0)
  {}
  
  ~GraphicsAPI() = default;
  
  virtual bool 
  init(WeakPtr<DisplaySurface> windowHandler) = 0;
  
  virtual void 
  cleanUpResources() = 0;
  
  virtual SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> handle,
                  GAPI_FORMAT::k = GAPI_FORMAT::FORMAT_UNKNOWN) = 0;

  virtual SPtr<ConstBuffer> 
  createConstBuffer(const uint32 byteWitdh = 0,
                    void* data = nullptr,
                    uint32 indexCount = 0) = 0;

  virtual SPtr<Indexbuffer>
  createIndexBuffer(const uint32 byteWidth = 0,
                    void* data = nullptr,
                    uint32 indexCount = 0) = 0;

  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 byteWidth = 0,
                    void* data = nullptr,
                    uint32 indexCount = 0) = 0;

  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer) = 0;

  virtual void
  setIndexBuffer(WeakPtr<Indexbuffer> buffer) = 0;

  virtual void
  setVertexBuffer(WeakPtr<VertexBuffer> buffer) = 0;

  virtual void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWidth,
                    void* data = nullptr) = 0;

 protected:
	 uint32 m_shaderModel;

};// GraphicsAPI class
}/// namespace bowEngineSDK
