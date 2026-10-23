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
#include "bowSwapChain.h"
#include "bowTopology.h"
#include "bowDepthstencilView.h"
#include "bowViewPort.h"

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

  /*
  * @brief
  *  Default constructor.
  *  Sets te shader model as 0.
  */
  GraphicsAPI():
   m_shaderModel(0)
  {}
  
  /*
  * @brief
  *  Default destructor.
  */
  ~GraphicsAPI() = default;
  
  /*
  * @brief
  *  Initialize the graphics api.
  * @param WeakPtr<DisplaySurface>
  * @return none
  */
  virtual bool 
  init(WeakPtr<DisplaySurface> windowHandler) = 0;
  
  /*
  * @brief
  *  Clean up function.
  * @param none
  * @return none
  */
  virtual void 
  cleanUpResources() = 0;

  /// SwapChain

  /*
  * @brief
  *  Creates the swap chain.
  * @param Weakptr<DisplaySurface>
  * @return SharedPtr SwapChain
  */
  virtual SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> handle,
                  GAPI_FORMAT::E = GAPI_FORMAT::FORMAT_UNKNOWN) = 0;

  /// Buffers

  /*
  * @brief
  *  Creates a constant buffer
  * @param const uint32
  * @return SharedPtr<ConstBuffer>
  */
  virtual SPtr<ConstBuffer> 
  createConstBuffer(const uint32 byteWitdh = 0,
                    uint32 _slot = 0) = 0;

  /*
  * @brief
  *  Creates an indexBuffer.
  * @param const uint32, void*
  * @return SharedPtr<IndeXBuffer>
  */
  virtual SPtr<Indexbuffer>
  createIndexBuffer(const uint32 byteWidth = 0, void* data = nullptr) = 0;

  /*
  * @brief
  *  Creates a vertex buffer.
  * @param const uint32, void*
  * @return SharedPtr<VertexBuffer>
  */
  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 byteWidth = 0, const void* _vertices = nullptr) = 0;

  /*
  * @brief
  *  Sets the const buffer and its initial data.
  * @param WeakPtr<ConstBuffer> void*
  * @retun none
  */
  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer, void* _data = nullptr) = 0;

  /*
  * @brief
  *  Sets an index buffer.
  * @param WeakPtr<IndexBuffer>
  * @return none
  */
  virtual void
  setIndexBuffer(WeakPtr<Indexbuffer> buffer) = 0;

  /*
  * @brief
  *  Sets the vertex buffer.
  * @param WeakPtr<vertexBuffer>
  * @return none
  */
  virtual void
  setVertexBuffer(WeakPtr<VertexBuffer> buffer) = 0;

  /*
  * @brief
  * Updates the Const buffer with new data.
  * @param WeakPtr, const uint32, void*
  * @return none
  */
  virtual void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWidth,
                    void* data = nullptr) = 0;

  /// Topology

  /*
  * @brief
  *  Creates a new topology.
  * @param Topology::TYPE
  * @return SharedPtr<Topology>
  */
  virtual SPtr<Topology>
  createTopology(Topology::Type _type = Topology::Type::TriangleList) = 0;

  /*
  * @brief
  *  Sets the topology.
  * @param WeakPtr<topology>
  * @reutn none
  */
  virtual void
  setTopology(WeakPtr<Topology> _topology) = 0;

  /// Depth stencil
  
  /*
  * @brief
  *  Creates a Depth Stencil view.
  * @param uint32, uint32
  * @re turn SharePtr<DepthStencilView>
  */
  virtual SPtr<DepthStencilView>
  createDepthStencil(uint32 _width = 0, uint32 _height = 0,
                     const GAPI_FORMAT::E  _format = GAPI_FORMAT::FORMAT_UNKNOWN) = 0;


  /*
  * @brief
  *  Creates a View Port.
  * @param foat, float, const GAPI_FORMAT
  * @return SharedPtr<ViewPort>
  */
  virtual SPtr<ViewPort>
  createViewPort(float _width = 0, float _height = 0,
                 const GAPI_FORMAT::E _format = GAPI_FORMAT::FORMAT_R8G8B8A8_UNKNOWN) = 0;


 protected:
	 uint32 m_shaderModel;

};// GraphicsAPI class
}/// namespace bowEngineSDK
