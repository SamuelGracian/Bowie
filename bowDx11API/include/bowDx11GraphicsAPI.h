#pragma once 

#include "bowGraphicsAPI.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class BOW_PLUGIN_EXPORT Dx11GraphicsAPI : public GraphicsAPI
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
  virtual bool
  init(WeakPtr<DisplaySurface> handlewindow) override;

  void
  cleanUpResources() override;

  virtual void
  draw(uint32 _vertexCount, uint32 _startVertexLocation) override;

  /*
  * @brief
  *  Create a swap chain.
  * @param WeakPtr<DisplaySurface> windowHandler, GAPI_FORMAT format
  * @return SharedPtr<SwapChain>
  */
  virtual SPtr<SwapChain>
  createSwapChain(WeakPtr<DisplaySurface> _windowHandler,
                  GAPI_FORMAT::E _format) override;

  /*
  * @brief
  * Create an empty buffer. It saves info in the update function.
  * @param const uint32 byteWith, const uint32 slot
  * @return
  */
  virtual SPtr<ConstBuffer>
  createConstBuffer(const uint32 byteWitdh,
                    const uint32 slot) override;

  /*
  * @brief
  * Creates and index buffer and sets an initial data.
  * @param uint32 bytewidth, void* data
  * @return sharedPtr<IndexBuffer>.
  */
  virtual SPtr<Indexbuffer>
  createIndexBuffer(const uint32 _byteWidth, void* data) override;

  /*
  * @brief
  *  Creates a vertex buffer.
  * @param uint32 byteWidth, const void* data
  * @return shared ptr <VertexBuffer>
  */
  virtual SPtr<VertexBuffer>
  createVertexBuffer(const uint32 _byteWidth, const void* _vertices) override;

  /*
  * @brief
  *  Sets the constant buffer with a given data.
  * @param weaKPtr<ConstBuffer>, void* data
  * @return void.
  */
  virtual void
  setConstBuffer(WeakPtr<ConstBuffer> buffer, void* _data) override;


  /*
  * @brief
  *  Sets the vertex buffer
  * @param WeakPtr<VertexBuffer>
  * @return none 
  */
  virtual void
  setVertexBuffer(WeakPtr<VertexBuffer> _buffer, uint32 _stride,
                  uint32 _offset) override;

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

  /*
  * @brief
  *  Sets the topology.
  * @param WeakPtr<Topology> topology.
  * @return none
  */
  virtual void
  setTopology(WeakPtr<Topology> _topology) override;

  /*
  * @brief
  *  Create a depth stencil.
  * @param uint32 width, uint32 height, const GAPI_FORMAT format
  * @return SharedPtr<DepthStencilView>
  */
  virtual SPtr<DepthStencilView>
  createDepthStencil(uint32 _width, uint32 _height,
                     const GAPI_FORMAT::E _format) override;


  virtual SPtr <ViewPort> /// TO DO: create an actual implementation for the view port
  createViewPort()override;


  virtual SPtr<VertexShader>
  createVertexShader(const String& _shaderCode, const String& _entryPoint,
                     Vector<String> _defines) override;

  virtual void
  setVertexShader(WeakPtr<VertexShader> _shader) override;


  virtual SPtr<PixelShader>
  createPixelShader(const String& _shaderCode, const String& _entryPoint,
                    Vector<String> _defines) override;

  virtual void
  setPixelShader(WeakPtr<PixelShader> _shader) override;

  SPtr<Texture2D>
  createTexture2D(const Vector<uint8>& _imgData, int32 _witdh,
                  int32 _height) override;

  SPtr<Texture2D>
  createTexture2DFromFile(const String& _filePath) override;

  void
  setTexture2D(uint32 _slot, WeakPtr<Texture2D> _texture) override;

  SPtr<RasterizerState>
  createRasterizerState(CULL_MODE::E _cullMode, FILL_MODE::E _fillMode,
                        bool _deathClip) override;

  void
  setRasterizerState(WeakPtr<RasterizerState> _rasterizer) override;

  SPtr<RenderTargetView>
  createRenderTargetView(uint32 _width, uint32 _height,
                         GAPI_FORMAT::E _format) override;

  void
  setRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                      WeakPtr<DepthStencilView> _deptStencill) override;

  void
  setRenderTargetViews(Vector<RenderTargetView>& _renderTargets,
                       WeakPtr<DepthStencilView> _depthStencil) override;

  void
  clearRenderTargetView(WeakPtr<RenderTargetView> _renderTarget,
                        float _color[4]) override;

  void
  clearDepthStencilView(WeakPtr<DepthStencilView> _depthStencil,
                        DepthStencilView::ClearFlags _flag,
                          float _depth, uint32 _stencil) override;


  virtual SPtr <SamplerState>
  createSamplerState() override;

  virtual void
  setSamplerState(uint32 _slot, WeakPtr<SamplerState> _sampler) override;

  virtual SPtr<DepthStencilView>
  createShadowMap(uint32 _width, uint32 _height) = 0;

  virtual bool
  readShadowMap(WeakPtr<DepthStencilView> _shadowDepth,
                Vector<float>& outDepth) override;

  virtual void
  setShadowMap(uint32 _slot, WeakPtr<Texture2D> _mapTexture) override;

  virtual bool
  isOccluded(WeakPtr<DepthStencilView> _shadowDepth, const Vector3& worldPos,
             const Matrix4& _shadowView, const Matrix4 _shadowProjection,
             float bias) override;

  virtual void
  setShadowMapFromDepthView(uint32 _slot,
                            WeakPtr<DepthStencilView> _shadowDepth) override;

  /*  INTERNAL FUNCTIONS  */

  /*
  * @brief
  * @param HWND, uin32, uint32, GAPI_FORMAT, ID3D11Device
  *  Window handler, uint32 width, uint32 height,
  *  GAPI_FORMAT format
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
                        Vector<String> _defines, SHADER_TYPE::E _shaderType);
  
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
  const char*
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

  //Vector<uint8>
  //loadImageFromFileInternal(const String& _filePath, int32* _width, int32 _height,
  //                  int32* _chanels);

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
