/************************************************************************/
/**
 * @file bowGraphicsAPI.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 * Core interface for the graphics API.
 */
 /*************************************************************************/
#pragma once

#include "bowCoreRequisites.h"
#include "bowModule.h"

namespace bowEngineSDK
{
class ConstBuffer;
class DepthStencilView;
class DisplaySurface;
class IndexBuffer;
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

  /**
  * @brief
  *  Default constructor.
  */
  GraphicsAPI() = default;
  
  /**
  * @brief
  *  Default destructor.
  */
  virtual ~GraphicsAPI();
  
  /**
  * @brief
  *  Initialize the graphics api.
  * @param WeakPtr<DisplaySurface>
  * @return none
  */
  virtual bool 
  init(WeakPtr<DisplaySurface> windowHandler) = 0;
  
  /**
  * @brief
  *  Renders an indexed geometry.
  * @param vertex Count, number of vertex to render,
     startVertexLocation start of the indexes to draw.
  * @return
  */
  virtual void
  draw(uint32 vertexCount = 0, uint32 startVertexLocation = 0) = 0;

  /**
  * @brief
  *  Clean up function.
  * @param none
  * @return none
  */
  virtual void 
  cleanUpResources() = 0;

  /// SwapChain

  /**
  * @brief
  *  Creates the swap chain.
  * @param handle: Pointer to the window
  * @return SharedPtr SwapChain
  */
  virtual SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> handle,
                  TEXTURE_FORMAT::E = TEXTURE_FORMAT::kFORMAT_UNKNOWN) = 0;

  /// Buffers

  /**
  * @brief
  *  Creates a constant buffer
  * @param byteWidth: byte width of the buffer,
     slot: slot to assign the buffer to.
  * @return Const buffer object.
  */
  virtual SPtr<ConstBuffer> 
  createConstBuffer(const uint32 byteWitdh = 0,
                    uint32 slot = 0) = 0;

  /**
  * @brief
  *  Creates an indexBuffer.
  * @param byteWidth: byte width of the buffer,
     data: pointer to the data to the buffer.
  * @return SharedPtr<IndeXBuffer>
  */
  virtual SPtr<IndexBuffer>
  createIndexBuffer(const uint32 byteWidth = 0, void* data = nullptr) = 0;

  /**
  * @brief
  *  Creates a vertex buffer.
  * @param byteWidth: Buffer byte width, pointer to the vertices.
  * @return SharedPtr<VertexBuffer>
  */
  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 byteWidth = 0, const void* vertices = nullptr) = 0;

  /**
  * @brief
  *  Sets the const buffer in the immediate context.
  * @param buffer: const buffer to set.
  * @retun none
  */
  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer) = 0;

  /**
  * @brief
  *  Sets the index buffer in the immediate context.
  * @param buffer: Index buffer to set.
  * @return none
  */
  virtual void
  setIndexBuffer(WeakPtr<IndexBuffer> buffer) = 0;

  /**
  * @brief
  *  Sets the vertex buffer in the immediate context.
  * @param buffer: buffer to set in the immediate context,
     stride: size (in bytes) of the elements that are to be used from that vertex buffer,
     offset: number of bytes between the first element of a vertex buffer and 
     the first element to be used.
  * @return none
  */
  virtual void
  setVertexBuffer(WeakPtr<VertexBuffer> buffer, uint32 _stide,
                  uint32 _offset) = 0;

  /**
  * @brief
  * Updates the const buffer's data.
  * @param buffer: buffer to update, byteWitdh: byteWidth of the buffer,
     data: new data to update the buffer.
  * @return none
  */
  virtual void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWidth,
                    void* data = nullptr) = 0;

  /// Topology

  /**
  * @brief
  *  Creates a new topology object.
  * @param type: type of the topology.
  * @return Topology object.
  */
  virtual SPtr<Topology>
  createTopology(TOPOLOGY_TYPE::E _type = TOPOLOGY_TYPE::kTriangleList) = 0;

  /**
  * @brief
  *  Sets the topology to the immediate context.
  * @param topology: topology to set.
  * @return none
  */
  virtual void
  setTopology(WeakPtr<Topology> topology) = 0;

  /// Depth stencil
  
  /**
  * @brief
  *  Creates a Depth Stencil view.
  * @param width: texture width, height: texture height, format: texture format.
  * @return SharePtr<DepthStencilView>
  */
  virtual SPtr<DepthStencilView>
  createDepthStencil(uint32 width = 0, uint32 height = 0,
                     const TEXTURE_FORMAT::E  format = TEXTURE_FORMAT::kFORMAT_UNKNOWN) = 0;

  /// Shaders

  /**
  * @brief
  *  Creates vertex shader object.
  * @param shader code: shader code, entryPoint: entry point for the shader,
  *  defines: shaderModel: model of the shader.
  * @return
  */
  virtual SPtr<VertexShader>
  createVertexShader(const String& shaderCode, const String& entryPoint,
                     Vector<String>& defines, uint32 shaderModel = 5) = 0;
  /**
  * @brief
  *  Set the vertex shader in the immediate context.
  * @param shader: shader to set
  * @return none
  */
  virtual void
  setVertexShader(WeakPtr<VertexShader> shader ) = 0;

  /**
  * @brief
  *  Create a pixel Shader object.
  * @param shaderCode:HLSL shader code, entryPoint: function name for the entry 
  *  of the shader. defines: pre process macros, shader type, shader model.
  * @return pixel shader 
  */
  virtual SPtr<PixelShader>
  createPixelShader(const String& shaderCode, const String& entryPoint,
                    Vector<String>& defines, uint32 shaderModel = 5) = 0;

  /**
  * @brief
  *  Set the pixel shader in the immediate context.
  * @param shader: shader to set.
  * @return none.
  */
  virtual void
  setPixelShader(WeakPtr<PixelShader> shader) = 0;

  /**
  * @brief
  *  Creates a View Port.
  * @param width: window width, height: window height,
     maxDepth: max depth of the view port, Ranges between 0 and 1.
     minDepth: min depth of the view port, Ranges between 0 and 1.
  * @return ViewPort object.
  */
  virtual SPtr<ViewPort>
  createViewPort(float width, float height, float minDepth, float maxDepth,
                 float topLeftX, float topLeftY) = 0;

  /**
  * @brief
  *  Set the view Port in the immediate context.
  * @param viewPort: view port to set.
  * @return true if the  viewPort was set correctly.
  */
  virtual bool
  setViewPort(WeakPtr<ViewPort> viewPort) = 0;

  /// texture

  /**
  * @brief
  *  Creates a 2D texture with the data from an image.
  * @param imgData: data of the texture, width: texture Width,
     height: texture height.
  * @return 2D texture object.
  */
  virtual SPtr<Texture2D>
  createTexture2DWithImageData(const Vector<uint8>& imgData,
                               int32 witdh,
                               int32 height) = 0;

  /**
  * @brief
  *  Create a texture from a file.
  * @param filePath: path to the file.
  * @return 2D texture object.
  */
  SPtr<Texture2D>
  createTexture2DFromFile(const String& filePath);

  /**
  * @brief
  *  Sets the texture in the immediate context.
  * @param slot: slot to set the texture. texture: texture to set.
  * @return none.
  */
  virtual void
  setTexture2D(uint32 slot, WeakPtr<Texture2D> texture) = 0;

  /// rasterizer state

  /**
  * @brief
  *  Creates a rasterizer state object.
  * @param cullMode: cull mode, fillMode: fill mode,
     dethpClip: depth Clip for the rasterizer.
  * @return rasterizer state 
  */
  virtual SPtr<RasterizerState>
  createRasterizerState(CULL_MODE::E cullMode, FILL_MODE::E fillMode,
                        bool deathClip) = 0;

  /**
  * @brief
  *  Sets the rasterizer state in the immediate context.
  * @param rasterizer: rasterizer to set.
  * @return none.
  */
  virtual void
  setRasterizerState(WeakPtr<RasterizerState> rasterizer) = 0;

  /// render target view

  /**
  * @brief
  *  Creates a render target.
  * @param width: render target width, height: render target height.
     format: texture format.
  * @return
  */
  virtual SPtr<RenderTargetView>
  createRenderTargetView(uint32 width, uint32 height,
                         TEXTURE_FORMAT::E format) = 0;
  /**
  * @brief
  *  Sets the render target in the immediate context.
  * @param renderTarget: render target to set. depthStencil: depth stencil for
  *  the render target.
  * @return none.
  */
  virtual void
  setRenderTargetView(WeakPtr<RenderTargetView> renderTarget,
                      WeakPtr<DepthStencilView> deptStencill) = 0;

  /**
  * @brief
  *  Sets an array of render targets.
  * @param renderTargets: array of render targets,
     depthStencil: for the render targets.
  * @return none
  */
  virtual void
  setRenderTargetViews(Vector<WeakPtr<RenderTargetView>>& renderTargets,
                       WeakPtr<DepthStencilView> depthStencil) = 0;

  /**
  * @brief
  *  Sets all elements in the render target to one value.
  * @param renderTarget: render target to clear, color: value to set the render
  *  target.
  * @return none.
  */
  virtual void
  clearRenderTargetView(WeakPtr<RenderTargetView> renderTarget,
                        float color[4]) = 0;

  /**
  * @brief
  *  Clears the depth stencil resource.
  * @param depthStencil: depth stencil to clear, flag: new flag,
     depth: value to clear the depth buffer with, this value will be clamped 
     between 0 and 1. stencil: value to clear the stencil buffer with.
  * @return
  */
  virtual void
  clearDepthStencilView(WeakPtr<DepthStencilView> depthStencil,
                                   CLEAR_FLAGS::E flag,
                                   float depth, uint8 stencil) = 0;

  /// sampler state
  /**
  * @brief
  *  Create sampler state.
  * @param none
  * @return sampler State.
  */
  virtual SPtr <SamplerState>
  createSamplerState() = 0;

  /**
  * @brief
  *  Set the sampler state.
  * @param slot: slot to assign the sampler. sampler: sampler to set.
  * @return none.
  */
  virtual void
  setSamplerState(uint32 slot, WeakPtr<SamplerState> sampler) = 0;

  /// shadow map

  /**
  * @brief
  *  Creates a shadow map texture.
  * @param width: texture width, height: texture height.
  * @return DepthStencilView.
  */
  virtual SPtr<DepthStencilView>
  createShadowMap(uint32 width, uint32 height) = 0;

  /**
  * @brief
  *  Reads a shadow map.
  * @param shadowDepth: shadow map to read. outDepth: Vector to save the depth values.
  * @return true if readied successfully.
  */
  virtual bool
  readShadowMap(WeakPtr<DepthStencilView> shadowDepth,
                Vector<float>& outDepth) = 0;

  /**
  * @brief
  *  Set the shadow map.
  * @param slot: slot to set the map texture. mapTexture: map texture to set.
  * @return none
  */
  virtual void
  setShadowMap(uint32 slot, WeakPtr<Texture2D> mapTexture) = 0;
  
  /**
  * @brief
     Checks if one pixel is occluded or not.
  * @param shadowDepth: shadow map with the depth values,
     wordlPos: position in the world to be checked.
     shadowView: view matrix that generates the shadow map.
     shadowProjection: projection matrix that generates the shadow map.
     bias: depth value.
  * @return true if the pixel is occluded
  */
  virtual bool
  isOccluded(WeakPtr<DepthStencilView> shadowDepth, const Vector3& worldPos,
             const Matrix4& shadowView, const Matrix4 shadowProjection,
             float bias) = 0;

  /**
  * @brief
  *  Sets a shadow map.
  * @param slot: slot to assign the shadow map. shadowMap: map to assign.
  * @return none
  */
  virtual void
  setShadowMapFromDepthView(uint32 slot,
                            WeakPtr<DepthStencilView> shadowDepth) = 0;
};
}/// name space bowEngineSDK
