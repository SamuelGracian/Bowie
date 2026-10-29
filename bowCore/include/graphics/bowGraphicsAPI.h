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
#include "bowVertexShader.h"
#include "bowPixelShader.h"
#include "bowModule.h"
#include "bowRasterizerState.h"
#include "bowSamplerState.h"

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

class BOW_CORE_EXPORT GraphicsAPI : public Module <GraphicsAPI>
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
  virtual ~GraphicsAPI();
  
  /*
  * @brief
  *  Initialize the graphics api.
  * @param WeakPtr<DisplaySurface>
  * @return none
  */
  virtual bool 
  init(WeakPtr<DisplaySurface> windowHandler) = 0;
  
  virtual void
  draw(uint32 _vertexCount = 0, uint32 _startVertexLocation = 0) = 0;

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
  setVertexBuffer(WeakPtr<VertexBuffer> buffer, uint32 _stide,
                  uint32 _offset) = 0;

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

  /// Shaders
  virtual SPtr<VertexShader>
  createVertexShader(const String& _shaderCode, const String& _entryPoint,
                     Vector<String> _defines) = 0;

  virtual void
  setVertexShader(WeakPtr<VertexShader> _shader ) = 0;

  virtual SPtr<PixelShader>
  createPixelShader(const String& _shaderCode, const String& _entryPoint,
                    Vector<String> _defines) = 0;

  virtual void
  setPixelShader(WeakPtr<PixelShader> _shader) = 0;

  /*
  * @brief
  *  Creates a View Port.
  * @param foat, float, const GAPI_FORMAT
  * @return SharedPtr<ViewPort>
  */
  virtual SPtr<ViewPort>
  createViewPort() = 0;

  /// texture
  //virtual Vector<uint8>
  //loadImageFromFile(const String& _filePath, int32* _width, int32* _height,
  //                  int32* _channels) = 0;

  virtual SPtr<Texture2D>
  createTexture2D(const Vector<uint8>& _imgData, int32 _witdh,
                  int32 _height) = 0;

  //virtual SPtr<Texture2D>
  //createTexture2DFromFile(const String& _filePath) = 0;

  virtual void
  setTexture2D(uint32 _slot, WeakPtr<Texture2D> _texture) = 0;

  /// rasterizer state
  virtual SPtr<RasterizerState>
   createRasterizerState(CULL_MODE::E _cullMode, FILL_MODE::E _fillMode,
                         bool _deathClip) = 0;

  virtual void
  setRasterizerState(WeakPtr<RasterizerState> _rasterizer) = 0;

  /// render target view

  virtual SPtr<RenderTargetView>
  createRenderTargetView(uint32 _width, uint32 _height,
                         GAPI_FORMAT::E _format) = 0;

  virtual void
   setRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                       WeakPtr<DepthStencilView> _deptStencill) = 0;

  virtual void
  setRenderTargetViews(Vector<WeakPtr<RenderTargetView>>& _renderTargets,
                       WeakPtr<DepthStencilView> _depthStencil) = 0;

  virtual void
  clearRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                        float _color[4]) = 0;

  virtual void
  clearDepthStencilView(WeakPtr<DepthStencilView> _depthStencil,
                                   DepthStencilView::ClearFlags _flag,
                                   float _depth, uint8 _stencil) = 0;

  /// sampler state
  virtual SPtr <SamplerState>
  createSamplerState() = 0;

  virtual void
  setSamplerState(uint32 _slot, WeakPtr<SamplerState> _sampler) = 0;

  /// shadow map
  virtual SPtr<DepthStencilView>
  createShadowMap(uint32 _width, uint32 _height) = 0;

  virtual bool
  readShadowMap(WeakPtr<DepthStencilView> _shadowDepth,
                Vector<float>& outDepth) = 0;

  virtual void
  setShadowMap(uint32 _slot, WeakPtr<Texture2D> _mapTexture) = 0;

  virtual bool
  isOccluded(WeakPtr<DepthStencilView> _shadowDepth, const Vector3& worldPos,
             const Matrix4& _shadowView, const Matrix4 _shadowProjection,
             float bias) = 0;

  virtual void
  setShadowMapFromDepthView(uint32 _slot,
                            WeakPtr<DepthStencilView> _shadowDepth) = 0;

 protected:
	 uint32 m_shaderModel;

};// GraphicsAPI class
}/// namespace bowEngineSDK

/*
* rasterizer state and functions, // Dx11 file 
* render target //
* depth stencil //
* create and set sampler /// 
* Shadow functions///
*/