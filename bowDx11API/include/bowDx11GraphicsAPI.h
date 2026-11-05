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
class Indexbuffer;
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
  /*
  * @brief
  *  Default constructor.
  */
  Dx11GraphicsAPI() = default;

  /*
  * @brief
  *  Initialize function.
  * @param WeakPtr<DisplaySurface> windowHandler
  * @return bool
  */
  bool
  init(WeakPtr<DisplaySurface> handlewindow) override;

  void
  cleanUpResources() override;

  void
  draw(uint32 _vertexCount, uint32 _startVertexLocation) override;

  /*
  * @brief
  *  Create a swap chain.
  * @param WeakPtr<DisplaySurface> windowHandler, TEXTURE_FORMAT format
  * @return SharedPtr<SwapChain>
  */
  SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> _windowHandler,
                  TEXTURE_FORMAT::E _format) override;

  /*
  * @brief
  * Create an empty buffer. It saves info in the update function.
  * @param const uint32 byteWith, const uint32 slot
  * @return
  */
  SPtr<ConstBuffer>
  createConstBuffer(const uint32 byteWitdh,
                    const uint32 slot) override;

  /*
  * @brief
  * Creates and index buffer and sets an initial data.
  * @param uint32 bytewidth, void* data
  * @return sharedPtr<IndexBuffer>.
  */
  SPtr<Indexbuffer>
  createIndexBuffer(const uint32 _byteWidth, void* data) override;

  /*
  * @brief
  *  Creates a vertex buffer.
  * @param uint32 byteWidth, const void* data
  * @return shared ptr <VertexBuffer>
  */
  SPtr<VertexBuffer>
  createVertexBuffer(const uint32 _byteWidth, const void* _vertices) override;

  /*
  * @brief
  *  Sets the constant buffer with a given data.
  * @param weaKPtr<ConstBuffer>, void* data
  * @return void.
  */
  void
  setConstBuffer(WeakPtr<ConstBuffer> buffer) override;


  /*
  * @brief
  *  Sets the vertex buffer
  * @param WeakPtr<VertexBuffer>
  * @return none 
  */
  void
  setVertexBuffer(WeakPtr<VertexBuffer> _buffer, uint32 _stride,
                  uint32 _offset) override;

  /*
  * @brief
  *  Gets a bowie index buffer, internali turns it into a Dx11 buffer and sets it.
  * @param weakPtr <IndexBuffer>
  * @return void
  */
  void
  setIndexBuffer(WeakPtr<Indexbuffer> buffer) override;

  /*
  * @brief
  *  Updates the info in the given const buffer.
  * @param weakPtr <constBUffer>, const uint32 byteWidth.
  * @return void
  */
  void
  updateConstBuffer(WeakPtr<ConstBuffer> buffer, const uint32 byteWitdth,
                    void* data = nullptr) override;

  /*
  * @brief
  *  Creates a topology.
  *  Sets as default the topology as a Triangle list.
  * @param TOPOLOGY::TYPE
  * @return SharedPtr Topology
  */
  SPtr<Topology>
  createTopology(TOPOLOGY_TYPE::E _type) override;

  /*
  * @brief
  *  Sets the topology.
  * @param WeakPtr<Topology> topology.
  * @return none
  */
  void
  setTopology(WeakPtr<Topology> _topology) override;

  /*
  * @brief
  *  Create a depth stencil.
  * @param uint32 width, uint32 height, const TEXTURE_FORMAT format
  * @return SharedPtr<DepthStencilView>
  */
  SPtr<DepthStencilView>
  createDepthStencil(uint32 _width, uint32 _height,
                     const TEXTURE_FORMAT::E _format) override;


  SPtr <ViewPort> /// TO DO: create an actual implementation for the view port
  createViewPort(float width, float height, float minDepth, float maxDepth,
                 float topLeftX, float topLeftY)override;

  bool
  setViewPort(WeakPtr<ViewPort> _viewPort) override;

  SPtr<VertexShader>
  createVertexShader(const String& _shaderCode, const String& _entryPoint,
                     Vector<String>& _defines, uint32 _shaderModel) override;

  void
  setVertexShader(WeakPtr<VertexShader> _shader) override;


  SPtr<PixelShader>
  createPixelShader(const String& _shaderCode, const String& _entryPoint,
                    Vector<String>& _defines, uint32 _shaderModel) override;

  void
  setPixelShader(WeakPtr<PixelShader> _shader) override;

  SPtr<Texture2D>
  createTexture2DWithImageData(const Vector<uint8>& _imgData, int32 _witdh,
                  int32 _height) override;

  void
  setTexture2D(uint32 _slot, WeakPtr<Texture2D> _texture) override;

  SPtr<RasterizerState>
  createRasterizerState(CULL_MODE::E _cullMode, FILL_MODE::E _fillMode,
                        bool _deathClip) override;

  void
  setRasterizerState(WeakPtr<RasterizerState> _rasterizer) override;

  SPtr<RenderTargetView>
  createRenderTargetView(uint32 _width, uint32 _height,
                         TEXTURE_FORMAT::E _format) override;

  void
  setRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                      WeakPtr<DepthStencilView> _deptStencill) override;

  void
  setRenderTargetViews(Vector<WeakPtr<RenderTargetView>>& _renderTargets,
                       WeakPtr<DepthStencilView> _depthStencil) override;

  void
  clearRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                        float _color[4]) override;

  void
  clearDepthStencilView(WeakPtr<DepthStencilView> _depthStencil,
                        ClearFlags::E _flag,
                          float _depth, uint8 _stencil) override;


  SPtr <SamplerState>
  createSamplerState() override;

  void
  setSamplerState(uint32 _slot, WeakPtr<SamplerState> _sampler) override;

  SPtr<DepthStencilView>
  createShadowMap(uint32 _width, uint32 _height) override;

  bool
  readShadowMap(WeakPtr<DepthStencilView> _shadowDepth,
                Vector<float>& outDepth) override;

  /*
  * @brief
  *  Sets the texture for the shadowmap.
  * @param uint32 slot, WeaKptr mapTexture.
  * @reutn none 
  */
  void
  setShadowMap(uint32 _slot, WeakPtr<Texture2D> _mapTexture) override;

  /*
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

  /*
  * @brief
  *  Reads the shadow map from a depth view.
  * @param uint32 slot, WeakPtr<DepthStencil> shadowmap
  * @return none
  */
  void
  setShadowMapFromDepthView(uint32 _slot,
                            WeakPtr<DepthStencilView> _shadowDepth) override;

  /*  INTERNAL FUNCTIONS  */

  /*
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

  /*
  * @brief
  *  Gets the according DXGI format to the TEXTURE_FORMAT
  * @param TEXTURE_FORMAT
  * @return
  *  DXGI_FORMAT
  */
  DXGI_FORMAT
  getDx11FormatInternal(TEXTURE_FORMAT::E _format) const;

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
  * @param uint32 width, uint32 hieght, const TEXTURE_FORMAT, uint32 bindflag
  * @return ID3D11Texture2D*
  */
  ID3D11Texture2D*
  createTexture2DInternal(uint32 _width, uint32 _height,
                          const TEXTURE_FORMAT::E _format, uint32 _bindFlags);

  /*
  * @brief
  *  Getter for the dx11 bind flags.
  * @param const uint32 bindflag
  * @return uint32
  *  Value of the bind flag.
  */
  uint32
  getDx11BindFlagsInternal(const uint32 _bindFlag) const;

  ID3DBlob*
  compileShaderInternal(const String& _shaderCode, const String& _entryPoint,
                        Vector<String> _defines, SHADER_TYPE::E _shaderType,
                        uint32 _shaderModel);
  
  /*
  * @brief
  *  Creates an input layout.
  * @param ID3D10ShaderReflection
  * @return   Vector<D3D11_INPUT_ELEMENT_DESC>
  */
  Vector<D3D11_INPUT_ELEMENT_DESC>
  createInputLayoutInternal(ID3D11ShaderReflection* _reflection) const;

  /*
  * @brief
  * @param SHADER_TYPE, uint32
  *   shader type and shader model.
  * @return const char*
  */
  const ANISCHAR*
  getShaderModelInternal(SHADER_TYPE::E _shaderType, uint32 _shaderModel) const;

  /*
  * @brief
  *  Recieves a fill mode of type bowie and returns the Dx11 version fo it.
  * @param FILL_MODE
  * @return D3D11_FILL_MODE
  */
  D3D11_FILL_MODE
  getFillModeInternal(FILL_MODE::E _fillMode) const;

  /*
  * @brief
  *  recieves a cull mode of type bowie and returns the Dx11 version of it.
  * @param CULL_MODE
  * @reutrn D3D11_CULL_MODE
  */
  D3D11_CULL_MODE
  getCullModeInternal(CULL_MODE::E _cullMode) const;

private:

  /// <summary>
  /// Dx11 Device
  /// </summary>
  ID3D11Device* m_device = nullptr;

  /// <summary>
  /// Dx11 immediate context.
  /// </summary>
  ID3D11DeviceContext* m_immediateContext = nullptr;

};
}/// namespace GraphicsAPI
