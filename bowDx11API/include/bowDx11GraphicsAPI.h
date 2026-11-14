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
class Vector3;
class Vector4;
class DisplaySurface;
class SwapChain;
class ConstBuffer;
class IndexBuffer;
class VertexBuffer;
class Topology;
class DepthStencilView;
class PixelShader;
class VertexShader;
class ViewPort;
class Texture2D;
class SamplerState;
class Matrix4;
class RenderTargetView;
class RasterizerState;

class BOW_PLUGIN_EXPORT Dx11GraphicsAPI final : public GraphicsAPI
{
public:
  /**
  * @brief
  *  Default constructor.
  */
  Dx11GraphicsAPI() = default;

  /**
  * @brief
  *  Initialize function.
  * @param handleWindow: handler for the window.
  * @return bool
  */
  bool
  init(WeakPtr<DisplaySurface> handleWindow) override;
  
  /**
  * @brief
  *  Clean up function, releases all the objects.
  * @param none
  * @return none
  */
  void
  cleanUpResources() override;

  /**
  * @brief
  *  Draw indexed, non instanced primitives. Internally this function sets the 
  *  Base Vertex Location as 0
  * @param vertexCount: number of indices to draw.
  *  startVertexLocation: location of the first index read by the GPU from 
  the buffer.
  * @return none
  */
  void
  draw(uint32 vertexCount, uint32 startVertexLocation) override;

  /**
  * @brief
  *  Create a swap chain.
  * @param windowHandler: window handler, format: texture format.
  * @return SharedPtr<SwapChain>
  */
  SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> windowHandler,
                  TEXTURE_FORMAT::E format) override;

  /**
  * @brief
  * Create an empty buffer. It saves info in the update function.
  * @param byteWidth: buffer byte Width, slot: slot so assign the buffer to.
  * @return Const buffer object.
  */
  SPtr<ConstBuffer>
  createConstBuffer(const uint32 byteWitdh,
                    const uint32 slot) override;

  /**
  * @brief
  * Creates and index buffer and sets an initial data.
  * @param byteWisth: buffer byteWitdh, data: data to save in the indexbuffer.
  * @return sharedPtr<IndexBuffer>.
  */
   SPtr<IndexBuffer>
  createIndexBuffer(const uint32 byteWidth, void* data) override;

  /**
  * @brief
  *  Creates a vertex buffer.
  * @param byteWidtH: buffer byte width, vertices: model vertices.
  * @return Vertex buffer object.
  */
  SPtr<VertexBuffer>
  createVertexBuffer(const uint32 byteWidth, const void* vertices) override;

  /**
  * @brief
  *  Sets the constant buffer with a given data.
  * @param buffer: const buffer to be set.
  * @return void.
  */
  void
  setConstBuffer(WeakPtr<ConstBuffer> buffer) override;


  /**
  * @brief
  *  bind an array of vertex buffer to the input assembler stage.
  * @param buffer: vertex buffer to be set, stride: size of the elements that
  *  are to be used from that vertex, buffer.
  *  offset: one offset value for each buffer in the vertex buffer array.
  * @return none 
  */
  void
  setVertexBuffer(WeakPtr<VertexBuffer> buffer, uint32 stride,
                  uint32 offset) override;

  /**
  * @brief
  *  Gets a bowie index buffer, internally turns it into a Dx11 buffer and sets it.
  * @param buffer: index buffer to be set.
  * @return void
  */
  void
  setIndexBuffer(WeakPtr<IndexBuffer> buffer) override;

  /**
  * @brief
  *  Updates the info in the given const buffer.
  * @param buffer: buffer object to update, byteWitdh: new byte width of the buffer.
  *  data: data to update the const buffer with.
  * @return void
  */
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
  SPtr<Topology>
  createTopology(TOPOLOGY_TYPE::E type) override;

  /**
  * @brief
  *  Sets the topology.
  * @param topology: topology to set.
  * @return none
  */
  void
  setTopology(WeakPtr<Topology> topology) override;

  /**
  * @brief
  *  Create a depth stencil.
  * @param with: texture width, height: texture height, format: texture format.
  * @return SharedPtr<DepthStencilView>
  */
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
  SPtr <ViewPort>
  createViewPort(float width, float height, float minDepth, float maxDepth,
                 float topLeftX, float topLeftY)override;
  /**
  * @brief
  *  Set the view Port in the immediate context.
  * @param viewPort: view port to set.
  * @return true if the  viewPort was set correctly.
  */
  bool
  setViewPort(WeakPtr<ViewPort> _viewPort) override;

  /**
  * @brief
  *  Creates vertex shader object.
  * @param shader code: shader code, entryPoint: entry point for the shader,
  *  defines: shaderModel: model of the shader.
  */
  SPtr<VertexShader>
  createVertexShader(const String& _shaderCode, const String& _entryPoint,
                     Vector<String>& _defines, uint32 _shaderModel) override;

  /**
  * @brief
  *  Set the vertex shader in the immediate context.
  * @param shader: shader to set
  * @return
  */
  void
  setVertexShader(WeakPtr<VertexShader> _shader) override;

  /**
  * @brief
  * @param shaderCode:HLSL shader code, entryPoint: function name for the entry
  *  of the shader. defines: pre process macros, shader type, shader model.
  * @return pixel shader
  */
  SPtr<PixelShader>
  createPixelShader(const String& _shaderCode, const String& _entryPoint,
                    Vector<String>& _defines, uint32 _shaderModel) override;

  /**
  * @brief
  *  Sets the pixel shader in the immediate context.
  * @param shader: shader to set.
  * @return none
  */
  void
  setPixelShader(WeakPtr<PixelShader> _shader) override;

  /**
  * @brief
  *  Creates a 2D texture with the data from an image.
  * @param imgData: data of the texture, width: texture Width,
     height: texture height.
  * @return 2D texture object.
  */
  SPtr<Texture2D>
  createTexture2DWithImageData(const Vector<uint8>& _imgData, int32 _witdh,
                  int32 _height) override;

  /**
  * @brief
  *  Sets the texture in the immediate context.
  * @param slot: slot to set the texture. texture: texture to set.
  * @return none.
  */
  void
  setTexture2D(uint32 _slot, WeakPtr<Texture2D> _texture) override;

  /**
  * @brief
  *  Creates a rasterizer state object.
  * @param cullMode: cull mode, fillMode: fill mode,
  * dethpClip: depth Clip for the rasterizer.
  * @return rasterizer state
  */
  SPtr<RasterizerState>
  createRasterizerState(CULL_MODE::E _cullMode, FILL_MODE::E _fillMode,
                        bool _deathClip) override;

  /**
  * @brief
  *  Sets the rasterizer state in the immediate context.
  * @param rasterizer: rasterizer to set.
  * @return
  */
  void
  setRasterizerState(WeakPtr<RasterizerState> _rasterizer) override;

  /**
  * @brief
  *  Creates a render target.
  * @param width: render target width, height: render target height.
     format: texture format.
  * @return
  */
  SPtr<RenderTargetView>
  createRenderTargetView(uint32 _width, uint32 _height,
                         TEXTURE_FORMAT::E _format) override;

  /**
  * @brief
  *  Sets the render target in the immediate context.
  * @param renderTarget: render target to set. depthStencil: depth stencil for
  *  the render target.
  * @return none.
  */
  void
  setRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                      WeakPtr<DepthStencilView> _deptStencill) override;

  /**
  * @brief
  *  Sets an array of render targets.
  * @param renderTargets: array of render targets,
     depthStencil: for the render targets.
  * @return none
  */
  void
  setRenderTargetViews(Vector<WeakPtr<RenderTargetView>>& _renderTargets,
                       WeakPtr<DepthStencilView> _depthStencil) override;

  /**
  * @brief
  *  Sets all elements in the render target to one value.
  * @param renderTarget: render target to clear, color: value to set the render
  *  target.
  * @return none.
  */
  void
  clearRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                        float _color[4]) override;

  /**
  * @brief
  *  Clears the depth stencil resource.
  * @param depthStencil: depth stencil to clear, flag: new flag,
     depth: value to clear the depth buffer with, this value will be clamped
     between 0 and 1. stencil: value to clear the stencil buffer with.
  * @return
  */
  void
  clearDepthStencilView(WeakPtr<DepthStencilView> _depthStencil,
                        ClearFlags::E _flag,
                          float _depth, uint8 _stencil) override;

  /**
  * @brief
  *  Create sampler state.
  * @param none
  * @return sampler State.
  */
  SPtr <SamplerState>
  createSamplerState() override;

  /**
  * @brief
  *  Set the sampler state.
  * @param slot: slot to assign the sampler. sampler: sampler to set.
  * @return none.
  */
  void
  setSamplerState(uint32 _slot, WeakPtr<SamplerState> _sampler) override;

  /**
  * @brief
  *  Creates a shadow map texture.
  * @param width: texture width, height: texture height.
  * @return DepthStencilView.
  */
  SPtr<DepthStencilView>
  createShadowMap(uint32 _width, uint32 _height) override;

  /**
  * @brief
  *  Reads a shadow map.
  * @param shadowDepth: shadow map to read. outDepth: Vector to save the depth values.
  * @return true if readied successfully.
  */
  bool
  readShadowMap(WeakPtr<DepthStencilView> _shadowDepth,
                Vector<float>& outDepth) override;

  /**
  * @brief
  *  Sets the texture for the shadow map.
  * @param uint32 slot, WeaKptr mapTexture.
  * @reutn none 
  */
  void
  setShadowMap(uint32 _slot, WeakPtr<Texture2D> _mapTexture) override;

  /**
  * @brief
  *  Checks if a pixel is being occluded to decide to draw it or no.
  * @param WeakPtr<DepthStencilView> shadowDepth, Vector3 worldPos,
  *  Matrix4 shadowView, Matrix4 shadowProjection, float bias.
  * @return bool
  */
  bool
  isOccluded(WeakPtr<DepthStencilView> _shadowDepth, const Vector3& worldPos,
             const Matrix4& _shadowView, const Matrix4 _shadowProjection,
             float bias) override;

  /**
  * @brief
  *  Reads the shadow map from a depth view.
  * @param uint32 slot, WeakPtr<DepthStencil> shadow map
  * @return none
  */
  void
  setShadowMapFromDepthView(uint32 _slot,
                            WeakPtr<DepthStencilView> _shadowDepth) override;

  /*  INTERNAL FUNCTIONS  */

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
  getDx11FormatInternal(TEXTURE_FORMAT::E _format) const;

  /**
  * @brief
  * create back buffer for the render target.
  * @param IDXGISwapChain*
  * @return ID3D11RendertTargetView*
  */
  ID3D11RenderTargetView*
  createBackBufferRTInternal(IDXGISwapChain* _swapChain);

  /**
  * @brief
  *  Creates a texture of Dx11 type.
  * @param uint32 width, uint32 height, const TEXTURE_FORMAT, uint32 bind flag
  * @return ID3D11Texture2D*
  */
  ID3D11Texture2D*
  createTexture2DInternal(uint32 _width, uint32 _height,
                          const TEXTURE_FORMAT::E _format, uint32 _bindFlags);

  /**
  * @brief
  *  Getter for the dx11 bind flags.
  * @param const uint32 bind flag
  * @return uint32
  *  Value of the bind flag.
  */
  uint32
  getDx11BindFlagsInternal(const uint32 _bindFlag) const;

  /**
  * @brief
  * @param
  * @return
  */
  ID3DBlob*
  compileShaderInternal(const String& _shaderCode, const String& _entryPoint,
                        Vector<String> _defines, SHADER_TYPE::E _shaderType,
                        uint32 _shaderModel);
  
  /**
  * @brief
  *  Creates an input layout.
  * @param ID3D10ShaderReflection
  * @return   Vector<D3D11_INPUT_ELEMENT_DESC>
  */
  Vector<D3D11_INPUT_ELEMENT_DESC>
  createInputLayoutInternal(ID3D11ShaderReflection* _reflection) const;

  /**
  * @brief
  * @param SHADER_TYPE, uint32
  *   shader type and shader model.
  * @return const char*
  */
  const ANISCHAR*
  getShaderModelInternal(SHADER_TYPE::E _shaderType, uint32 _shaderModel) const;

  /**
  * @brief
  *  Receives a fill mode of type bowie and returns the Dx11 version fo it.
  * @param FILL_MODE
  * @return D3D11_FILL_MODE
  */
  D3D11_FILL_MODE
  getFillModeInternal(FILL_MODE::E _fillMode) const;

  /**
  * @brief
  *  receives a cull mode of type bowie and returns the Dx11 version of it.
  * @param CULL_MODE
  * @reutrn D3D11_CULL_MODE
  */
  D3D11_CULL_MODE
  getCullModeInternal(CULL_MODE::E _cullMode) const;

private:

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
