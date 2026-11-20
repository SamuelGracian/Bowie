/************************************************************************/
/**
 * @file bowDx11GraphicsAPI.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 * DX11 implementation for graphics API.
 */
 /*************************************************************************/
#pragma once 

#include "bowGraphicsAPI.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{

class BOW_PLUGIN_EXPORT Dx11GraphicsAPI final : public GraphicsAPI
{
  /*  INTERNAL FUNCTIONS  */
private:
  /**
  * @brief
  * @param HWND, uin32, uint32, TEXTURE_FORMAT, ID3D11Device
  *  Window handler, uint32 width, uint32 height,
  *  TEXTURE_FORMAT format
  * @return IDXGISwapChain
  *  Returns a pointer of type swap chain.
  */
  IDXGISwapChain*
  createSwapChainInternal(HWND hwnd, uint32 width,
                          uint32 height,
                          TEXTURE_FORMAT::E format);

  /**
  * @brief
  *  Gets the according DXGI format to the TEXTURE_FORMAT
  * @param TEXTURE_FORMAT
  * @return
  *  DXGI_FORMAT
  */
  DXGI_FORMAT
  getDx11FormatInternal(TEXTURE_FORMAT::E format) const;

  /**
  * @brief
  * create back buffer for the render target.
  * @param IDXGISwapChain*
  * @return ID3D11RendertTargetView*
  */
  ID3D11RenderTargetView*
  createBackBufferRTInternal(IDXGISwapChain* swapChain);

  /**
  * @brief
  *  Creates a texture of Dx11 type.
  * @param uint32 width, uint32 height, const TEXTURE_FORMAT, uint32 bind flag
  * @return ID3D11Texture2D*
  */
  ID3D11Texture2D*
  createTexture2DInternal(uint32 width, uint32 height,
                          const TEXTURE_FORMAT::E format, uint32 bindFlags);

  /**
  * @brief
  *  Getter for the dx11 bind flags.
  * @param const uint32 bind flag
  * @return uint32
  *  Value of the bind flag.
  */
  uint32
  getDx11BindFlagsInternal(const uint32 bindFlag) const;

  /**
  * @brief
  * @param
  * @return
  */
  ID3DBlob*
  compileShaderInternal(const String& shaderCode, const String& entryPoint,
                        Vector<String>& defines, SHADER_TYPE::E shaderType,
                          uint32 shaderModel) const;

  /**
  * @brief
  *  Creates an input layout.
  * @param ID3D10ShaderReflection
  * @return   Vector<D3D11_INPUT_ELEMENT_DESC>
  */
  Vector<D3D11_INPUT_ELEMENT_DESC>
  createInputLayoutInternal(ID3D11ShaderReflection* reflection) const;

  /**
  * @brief
  * @param SHADER_TYPE, uint32
  *   shader type and shader model.
  * @return const char*
  */
  const char*
  getShaderModelInternal(SHADER_TYPE::E shaderType, uint32 shaderModel) const;

  /**
  * @brief
  *  Receives a fill mode of type bowie and returns the Dx11 version fo it.
  * @param FILL_MODE
  * @return D3D11_FILL_MODE
  */
  D3D11_FILL_MODE
  getFillModeInternal(FILL_MODE::E fillMode) const;

  /**
  * @brief
  *  receives a cull mode of type bowie and returns the Dx11 version of it.
  * @param CULL_MODE
  * @reutrn D3D11_CULL_MODE
  */
  D3D11_CULL_MODE
  getCullModeInternal(CULL_MODE::E cullMode) const;

public:
  /**
  * @brief
  *  Default constructor.
  */
  Dx11GraphicsAPI() = default;

  ~Dx11GraphicsAPI();

  /**
  * @brief
  *  Initialize function.
  * @param handleWindow: handler for the window.
  * @return bool
  */
  virtual
  bool
  init(WeakPtr<DisplaySurface> handleWindow) override;
  


  /**
  * @brief
  *  Draw indexed, non instanced primitives. Internally this function sets the 
  *  Base Vertex Location as 0
  * @param indexCount: number of indices to drawIndexed.
  *  startIndexLocation: location of the first index read by the GPU from 
  the buffer.
  * @return none
  */
  virtual
  void
  drawIndexed(uint32 indexCount, uint32 startIndexLocation) override;

  /**
  * @brief
  *  Create a swap chain.
  * @param windowHandler: window handler, format: texture format.
  * @return SharedPtr<SwapChain>
  */
  virtual
  SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> windowHandler,
                  TEXTURE_FORMAT::E format) override;

  /**
  * @brief
  * Create an empty buffer. It saves info in the update function.
  * @param byteWidth: buffer byte Width, slot: slot so assign the buffer to.
  * @return Const buffer object.
  */
  virtual
  SPtr<ConstBuffer>
  createConstBuffer(const uint32 byteWitdh) override;

  /**
  * @brief
  * Creates and index buffer and sets an initial data.
  * @param byteWisth: buffer byteWitdh, data: data to save in the index buffer.
  * @return sharedPtr<IndexBuffer>.
  */
  virtual
   SPtr<IndexBuffer>
  createIndexBuffer(const uint32 byteWidth, void* data) override;

  /**
  * @brief
  *  Creates a vertex buffer.
  * @param byteWidtH: buffer byte width, vertices: model vertices.
  * @return Vertex buffer object.
  */
  virtual
  SPtr<VertexBuffer>
  createVertexBuffer(const uint32 byteWidth, const void* vertices) override;

  /**
  * @brief
  *  Sets the constant buffer with a given data.
  * @param buffer: const buffer to be set.
  *        slot: shader register slot/
  *        stages: shader stages receiving the buffer.
  * @return void.
  */
  virtual
  void
  setConstBuffer(WeakPtr<ConstBuffer> buffer,  uint32 slot,
                 uint32 Stages ) override;


  /**
  * @brief
  *  bind an array of vertex buffer to the input assembler stage.
  * @param buffer: vertex buffer to be set, stride: size of the elements that
  *  are to be used from that vertex, buffer.
  *  offset: one offset value for each buffer in the vertex buffer array.
  * @return none 
  */
  virtual
  void
  setVertexBuffer(WeakPtr<VertexBuffer> buffer, uint32 stride,
                  uint32 offset) override;

  /**
  * @brief
  *  Gets a bowie index buffer, internally turns it into a Dx11 buffer and sets it.
  * @param buffer: index buffer to be set.
  * @return void
  */
  virtual
  void
  setIndexBuffer(WeakPtr<IndexBuffer> buffer, TEXTURE_FORMAT::E format) override;

  /**
  * @brief
  *  Updates the info in the given const buffer.
  * @param buffer: buffer object to update, byteWitdh: new byte width of the buffer.
  *  data: data to update the const buffer with.
  * @return void
  */
  virtual
  void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWitdth,
                    void* data = nullptr) override;

  /**
  * @brief
  *  Creates a topology.
  *  Sets as default the topology as a Triangle list.
  * @param type: topology type.
  * @return SharedPtr Topology
  */
  virtual
  SPtr<Topology>
  createTopology(TOPOLOGY_TYPE::E type) override;

  /**
  * @brief
  *  Sets the topology.
  * @param topology: topology to set.
  * @return none
  */
  virtual
  void
  setTopology(TOPOLOGY_TYPE::E _type) override;

  /**
  * @brief
  *  Create a depth stencil.
  * @param with: texture width, height: texture height, format: texture format.
  * @return SharedPtr<DepthStencilView>
  */
  virtual
  SPtr<DepthStencilView>
  createDepthStencil(uint32 width, uint32 height,
                     const TEXTURE_FORMAT::E format) override;

  /**
  * @brief
  *  Creates a view port desc.
  * @param width: window width, height: window height,
     heightmaxDepth: max depth of the view port, Ranges between 0 and 1.
     minDepth: min depth of the view port, Ranges between 0 and 1.
  * @return
  */
  virtual
  SPtr <ViewPort>
  createViewPort(float width, float height, float minDepth, float maxDepth,
                 float topLeftX, float topLeftY)override;
  /**
  * @brief
  *  Set the view Port in the immediate context.
  * @param viewPort: view port to set.
  * @return true if the  viewPort was set correctly.
  */
  virtual
  bool
  setViewPort(WeakPtr<ViewPort> viewPort) override;

  /**
  * @brief
  *  Creates vertex shader object.
  * @param shader code: shader code, entryPoint: entry point for the shader,
  *  defines: shaderModel: model of the shader.
  */
  virtual
  SPtr<VertexShader>
  createVertexShader(const String& shaderCode, const String& entryPoint,
                     Vector<String>& defines, uint32 shaderModel) override;

  /**
  * @brief
  *  Set the vertex shader in the immediate context.
  * @param shader: shader to set
  * @return
  */
  virtual
  void
  setVertexShader(WeakPtr<VertexShader> shader) override;

  /**
  * @brief
  * @param shaderCode:HLSL shader code, entryPoint: function name for the entry
  *  of the shader. defines: pre process macros, shader type, shader model.
  * @return pixel shader
  */
  virtual
  SPtr<PixelShader>
  createPixelShader(const String& shaderCode, const String& entryPoint,
                    Vector<String>& defines, uint32 shaderModel) override;

  /**
  * @brief
  *  Sets the pixel shader in the immediate context.
  * @param shader: shader to set.
  * @return none
  */
  virtual
  void
  setPixelShader(WeakPtr<PixelShader> shader) override;

  /**
  * @brief
  *  Creates a 2D texture with the data from an image.
  * @param imgData: data of the texture, width: texture Width,
     height: texture height.
  * @return 2D texture object.
  */
  virtual
  SPtr<Texture2D>
  createTexture2DWithImageData(const Vector<uint8>& imgData, int32 witdh,
                  int32 height) override;

  /**
  * @brief
  *  Sets the texture in the immediate context.
  * @param slot: slot to set the texture. texture: texture to set.
  * @return none.
  */
  virtual
  void
  setTexture2D(uint32 slot, WeakPtr<Texture2D> texture) override;

  /**
  * @brief
  *  Creates a rasterizer state object.
  * @param cullMode: cull mode, fillMode: fill mode,
  * dethpClip: depth Clip for the rasterizer.
  * @return rasterizer state
  */
  virtual
  SPtr<RasterizerState>
  createRasterizerState(CULL_MODE::E cullMode, FILL_MODE::E fillMode,
                        bool depthClip) override;

  /**
  * @brief
  *  Sets the rasterizer state in the immediate context.
  * @param rasterizer: rasterizer to set.
  * @return
  */
  virtual
  void
  setRasterizerState(WeakPtr<RasterizerState> rasterizer) override;

  /**
  * @brief
  *  Creates a render target.
  * @param width: render target width, height: render target height.
     format: texture format.
  * @return
  */
  virtual
  SPtr<RenderTargetView>
  createRenderTargetView(uint32 width, uint32 height,
                         TEXTURE_FORMAT::E format) override;

  /**
  * @brief
  *  Sets the render target in the immediate context.
  * @param renderTarget: render target to set. depthStencil: depth stencil for
  *  the render target.
  * @return none.
  */
  virtual
  void
  setRenderTargetView(WeakPtr<RenderTargetView> renderTarget,
                      WeakPtr<DepthStencilView> deptStencill) override;

  /**
  * @brief
  *  Sets an array of render targets.
  * @param renderTargets: array of render targets,
     depthStencil: for the render targets.
  * @return none
  */
  virtual
  void
  setRenderTargetViews(Vector<WeakPtr<RenderTargetView>>& renderTargets,
                       WeakPtr<DepthStencilView> depthStencil) override;

  /**
  * @brief
  *  Sets all elements in the render target to one value.
  * @param renderTarget: render target to clear, color: value to set the render
  *  target.
  * @return none.
  */
  virtual
  void
  clearRenderTargetView(WeakPtr<RenderTargetView> renderTarget,
                        float color[4]) override;

  /**
  * @brief
  *  Clears the depth stencil resource.
  * @param depthStencil: depth stencil to clear, flag: new flag,
     depth: value to clear the depth buffer with, this value will be clamped
     between 0 and 1. stencil: value to clear the stencil buffer with.
  * @return
  */
  virtual
  void
  clearDepthStencilView(WeakPtr<DepthStencilView> _depthStencil,
                        CLEAR_FLAGS::E flag,
                          float depth, uint8 stencil) override;

  /**
  * @brief
  *  Create sampler state.
  * @param none
  * @return sampler State.
  */
  virtual
  SPtr <SamplerState>
  createSamplerState() override;

  /**
  * @brief
  *  Set the sampler state.
  * @param slot: slot to assign the sampler. sampler: sampler to set.
  * @return none.
  */
  virtual
  void
  setSamplerState(uint32 slot, WeakPtr<SamplerState> sampler) override;

  /**
  * @brief
  *  Creates a shadow map texture.
  * @param width: texture width, height: texture height.
  * @return DepthStencilView.
  */
  virtual
  SPtr<DepthStencilView>
  createShadowMap(uint32 width, uint32 height) override;

  /**
  * @brief
  *  Reads a shadow map.
  * @param shadowDepth: shadow map to read. outDepth: Vector to save the depth values.
  * @return true if readied successfully.
  */
  virtual
  bool
  readShadowMap(WeakPtr<DepthStencilView> shadowDepth,
                Vector<float>& outDepth) override;

  /**
  * @brief
  *  Sets the texture for the shadow map.
  * @param uint32 slot, WeaKptr mapTexture.
  * @reutn none 
  */
  virtual
  void
  setShadowMap(uint32 slot, WeakPtr<Texture2D> mapTexture) override;

  /**
  * @brief
  *  Checks if a pixel is being occluded to decide to drawIndexed it or no.
  * @param WeakPtr<DepthStencilView> shadowDepth, Vector3 worldPos,
  *  Matrix4 shadowView, Matrix4 shadowProjection, float bias.
  * @return bool
  */
  virtual
  bool
  isOccluded(WeakPtr<DepthStencilView> shadowDepth, const Vector3& worldPos,
             const Matrix4& shadowView, const Matrix4 shadowProjection,
             float bias) override;

  /**
  * @brief
  *  Reads the shadow map from a depth view.
  * @param uint32 slot, WeakPtr<DepthStencil> shadow map
  * @return none
  */
  virtual
  void
  setShadowMapFromDepthView(uint32 slot,
                            WeakPtr<DepthStencilView> shadowDepth) override;

  

private:

  /**
  * @brief
  *  Clean up function, releases all the objects.
  * @param none
  * @return none
  */
  virtual
  void
  cleanUpResources() override;

  /**
  * @brief
  *  Dx11 device
  */
  ID3D11Device* m_device = nullptr;

  /**
  * @brief
  *  Dx11 immediate context
  */
  ID3D11DeviceContext* m_immediateContext = nullptr;

};
}/// name space GraphicsAPI
