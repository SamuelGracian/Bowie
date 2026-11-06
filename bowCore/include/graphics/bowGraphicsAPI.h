#pragma once

#include "bowCoreRequisites.h"
#include "bowModule.h"

namespace bowEngineSDK
{
class ConstBuffer;
class DepthStencilView;
class DisplaySurface;
class Indexbuffer;
class Matrix4;
class PixelShader;
class RasterizerState;
class RenderTargetView;
class Texture2D;
class Topology;
class SamplerState;
class SwapChain;
class Vector3;
class Vector4;
class VertexBuffer;
class VertexShader;
class ViewPort;

class BOW_CORE_EXPORT GraphicsAPI : public Module <GraphicsAPI>
{
public:

  /*
  * @brief
  *  Default constructor.
  *  Sets te shader model as 0.
  */
  GraphicsAPI() = default;
  
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
                  TEXTURE_FORMAT::E = TEXTURE_FORMAT::FORMAT_UNKNOWN) = 0;

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
  setConstBuffer(WeakPtr<ConstBuffer> buffer) = 0;

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
  createTopology(TOPOLOGY_TYPE::E _type = TOPOLOGY_TYPE::TriangleList) = 0;

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
                     const TEXTURE_FORMAT::E  _format = TEXTURE_FORMAT::FORMAT_UNKNOWN) = 0;

  /// Shaders
  virtual SPtr<VertexShader>
  createVertexShader(const String& _shaderCode, const String& _entryPoint,
                     Vector<String>& _defines, uint32 _shaderModel) = 0;

  virtual void
  setVertexShader(WeakPtr<VertexShader> _shader ) = 0;

  virtual SPtr<PixelShader>
  createPixelShader(const String& _shaderCode, const String& _entryPoint,
                    Vector<String>& _defines, uint32 _shaderModel) = 0;

  virtual void
  setPixelShader(WeakPtr<PixelShader> _shader) = 0;

  /*
  * @brief
  *  Creates a View Port.
  * @param foat, float, const TEXTURE_FORMAT
  * @return SharedPtr<ViewPort>
  */
  virtual SPtr<ViewPort>
  createViewPort(float width, float height, float minDepth, float maxDepth,
                 float topLeftX, float topLeftY) = 0;

  virtual bool
  setViewPort(WeakPtr<ViewPort> _viewPort) = 0;

  /// texture

  virtual SPtr<Texture2D>
  createTexture2DWithImageData(const Vector<uint8>& _imgData,
                               int32 _witdh,
                               int32 _height) = 0;

  SPtr<Texture2D>
  createTexture2DFromFile(const String& _filePath);

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
                         TEXTURE_FORMAT::E _format) = 0;

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
                                   ClearFlags::E _flag,
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
};
}/// namespace bowEngineSDK
