#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>

#include "bowDx11GraphicsAPI.h"
#include "bowDx11RenderTargetView.h"
#include "bowMath.h"
#include "bowMatrix.h"
#include "bowVector4.h"
#include "bowVector3.h"
#include "bowSwapChain.h"
#include "bowWindow.h"

using namespace bowEngineSDK;


struct GeneralConstBuffer
{
  Matrix4 View;
  Matrix4 Perspective;
  Matrix4 worldMatrix;
  Matrix4 shadowView;
  Matrix4 shadowProjection;

  Vector3 cameraPosition;
  float Shininess;
};

Vector<String> defines { "#defines BOWIE_TEST" };
std::vector<uint8_t> neutralNormal = { 127, 127, 255, 255 };
std::vector<uint8_t> whitePixel = { 255, 255, 255, 255 };

struct MoveVertex
{
  float cosValue;
  float amplitude;
  float c;
  float d;
};

struct SimpleVertex
{
  Vector4 position;
  Vector4 normals;
  Vector4 tangent;
  Vector4 binormals;
  Vector2 texture;

  SimpleVertex(
    const Vector4& pos,
    const Vector4& normal,
    const Vector4& tan,
    const Vector4& binormal,
    const Vector2& tex)
    : position(pos), normals(normal), tangent(tan), binormals(binormal),
    texture(tex) {}
};/// Simple vertex struct

String
readFileToString(const std::wstring& _filePath) {
  const std::filesystem::path filePath(_filePath);
  const std::filesystem::path absolutePath =
    std::filesystem::absolute(filePath);

  std::ifstream file(absolutePath, std::ios::in | std::ios::binary);

  if (!file.is_open()) {
    std::wcerr
      << L"Unable to open file: "
      << absolutePath.wstring()
      << L"\nCurrent working directory: "
      << std::filesystem::current_path().wstring()
      << L"\n";

    return {};
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  if (file.fail() && !file.eof()) {
    std::wcerr
      << L"Error while reading file: "
      << absolutePath.wstring()
      << L"\n";

    return {};
  }

  return buffer.str();
}

int main() {
  
  /// VARIABLES
  bool running = true;
  /* WINDOW */
  float width = 800;
  float height = 600;
  /* DELTA TIME */
  auto pre = std::chrono::high_resolution_clock::now();
  float time = 0.0f;
  /* COLORS */
  float semiClearColor[4] = { 0.02f, 0.08f, 0.20f, 1.0f };
  /* FLAG */
  uint8 flag = ClearFlags::Depth | ClearFlags::Stencil;

  /// Cameras
  Vector3 Eye(150.0f, 150.0f, 500.0f);
  Vector3 At(0.0f, 0.0f, 0.0f);
  Vector3 Up(0.0f, 1.0f, 0.0f);


  Matrix4 view = Matrix4::lookAt(At, Eye, Up);
  Matrix4 perspective = Matrix4::perspective(Math::PI / 4.0f,
                                             width / height,
                                             0.01f,1000.0f);

  /// WORLD MATRIX AND TRANSLATIONS
  Matrix4 modelWorldScale = Matrix4::fromScaleVector(Vector3(50, 50, 50));
  Vector3 modelWorldTranslation(0.0f, 0.0f, 0.0f);

  /// INIT WINDOW
  auto window = std::make_shared<DisplaySurface>();

  if (!window->init(static_cast<int32>(width),static_cast<int32>(height),
                    "Bowie")) {

    std::cout << "Failed to start window" << std::endl;
    return -1;
  }

  GraphicsAPI::startUp<Dx11GraphicsAPI>();

  GraphicsAPI& grapi = GraphicsAPI::instance();

  /// WINDOW
  if (!grapi.init(window)) {
    GraphicsAPI::shutDown();
    std::cout << "Failed to init grapi" << std::endl;
    return -1;
  }

  /// SHADERS
  SPtr<PixelShader> p_ShaderShader = grapi.createPixelShader(
                                     readFileToString(L"RawData/Shaders.fxh"),
                                     "PShader",
                                     defines,
                                     4);
  if (!p_ShaderShader)     {
    std::cout << "Failed to create shader" << std::endl;
    return-1;
  }

  SPtr<PixelShader> p_pixelShader1 = grapi.createPixelShader(
                                   readFileToString(L"RawData/PixelShader.fxh"),
                                   "PShader",
                                   defines,
                                   4);
  if (!p_pixelShader1) {
    std::cout << "Failed to create pixel shader" << std::endl;
    return-1;
  }

  SPtr<VertexShader> p_vertexShader = grapi.createVertexShader(
    readFileToString(L"RawData/VertexShader.fxh"), "VShader", defines, 4);
  if (!p_vertexShader) {
    std::cout << "Failed to create vertex shader" << std::endl;
    return-1;
  }

  /// DEPTH STENCIL VIEW
  SPtr<DepthStencilView> p_depthSV = grapi.createDepthStencil(window->getClientWidth(),
                                                              window->getClientHeight(),
                                                              TEXTURE_FORMAT::D24_UNORM_S8_UINT);

  /// SWAP CHAIN
  SPtr<SwapChain> p_swapChain = grapi.createSwapChain(window,
                                         TEXTURE_FORMAT::R8G8B8A8_UNORM);

  if (!p_swapChain) {
    grapi.cleanUpResources();
    GraphicsAPI::shutDown();
    std::cout << "Failed to start swap chain" << std::endl;
    return -1;
  }

  /// RENDER TARGET VIEW
  Vector<WeakPtr<RenderTargetView>> gRenderTVS;
  gRenderTVS.push_back(p_swapChain->getRenderTargetView());

  /// SAMPLER STATE
  SPtr<SamplerState> p_sampler = grapi.createSamplerState();
  if (!p_sampler)     {
    std::cout << "Failed to create sampler" << std::endl;
    return -1;
  }

  ///const buffer for camera
  GeneralConstBuffer cameraData;
  cameraData.View = view;
  cameraData.Perspective = perspective;
  cameraData.worldMatrix = Matrix4::IDENTITY;
  cameraData.shadowView = Matrix4::IDENTITY;
  cameraData.shadowProjection = Matrix4::IDENTITY;
  cameraData.cameraPosition = Eye;
  cameraData.Shininess = 2;

  SPtr<ConstBuffer> p_constBufferCamera = 
    grapi.createConstBuffer(sizeof(GeneralConstBuffer),
                            0);

  /// CUBE OBJECTS
  Vector<SimpleVertex> cubeVertex {
    // Front
    // Normal (0,0,1)
    SimpleVertex({-1.0f, 1.0f, 1.0f, 1.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({ 1.0f,  1.0f, 1.0f, 1.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f}),

    SimpleVertex({ 1.0f, -1.0f, 1.0f, 1.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({-1.0f, -1.0f, 1.0f, 1.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f}),

    // BACK (-Z)
    SimpleVertex({ 1.0f, 1.0f, -1.0f, 1.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({-1.0f, 1.0f, -1.0f, 1.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f}),

    SimpleVertex({-1.0f, -1.0f, -1.0f, 1.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({ 1.0f, -1.0f, -1.0f, 1.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f}),

    // RIGHT (+X)
    SimpleVertex({ 1.0f, 1.0f, 1.0f, 1.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({ 1.0f,  1.0f, -1.0f, 1.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f}),

    SimpleVertex({ 1.0f, -1.0f, -1.0f, 1.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({1.0f, -1.0f,1.0f, 1.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, -1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f}),

    // LEFT (-X)
    SimpleVertex({-1.0f, 1.0f, -1.0f, 1.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({-1.0f, 1.0f, 1.0f, 1.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f}),

    SimpleVertex({-1.0f, -1.0f, 1.0f, 1.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({-1.0f, -1.0f, -1.0f, 1.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f}),

    // TOP (+Y)
    SimpleVertex({-1.0f, 1.0f, -1.0f, 1.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f,-1.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({ 1.0f, 1.0f, -1.0f, 1.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f,-1.0f, 0.0f},
                {1.0f, 0.0f}),

    SimpleVertex({ 1.0f, 1.0f, 1.0f, 1.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f,-1.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({-1.0f, 1.0f, 1.0f, 1.0f},
                 {0.0f, 1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f,-1.0f, 0.0f},
                 {0.0f, 1.0f}),

    // BOTTOM (-Y)
    SimpleVertex({-1.0f, -1.0f, 1.0f, 1.0f},
                 {0.0f, -1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 0.0f}),

    SimpleVertex({ 1.0f, -1.0f, 1.0f, 1.0f},
                 {0.0f,-1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 0.0f}),

    SimpleVertex({ 1.0f, -1.0f, -1.0f, 1.0f},
                 {0.0f, -1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {1.0f, 1.0f}),

    SimpleVertex({-1.0f, -1.0f, -1.0f, 1.0f},
                 {0.0f,-1.0f, 0.0f, 0.0f},
                 {1.0f, 0.0f, 0.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f})
  };

  Vector<uint16> cubeIndices = {
    /// front
    0,1,2,0,2,3,
    /// back
    4,5,6,4,6,7,
    /// right
    8,9,10,8,10,11,
    /// left
    12,13,14,12,14,15,
    /// Top
    16,17,18,16,18,19,
    /// bottom
    20,21,22,20,22,23
  };

  SPtr<VertexBuffer> p_cubeVertexBuffer = nullptr;
  SPtr<IndexBuffer> p_cubeIndexBuffer = nullptr;

  //uint32 cubeIndexCount = 0;

  SPtr<IndexBuffer> p_indexBuffer = nullptr;
  SPtr<VertexBuffer> p_vertexBuffer = nullptr;

  p_indexBuffer = grapi.createIndexBuffer(sizeof(uint16) * 
                                          static_cast<uint32> (cubeIndices.size()),
                                          cubeIndices.data());

  p_vertexBuffer = grapi.createVertexBuffer(sizeof(SimpleVertex) *
                                            static_cast<uint32>(cubeVertex.size()),
                                            cubeVertex.data());

  /// TOPOLOGY
  SPtr <Topology> p_topology = grapi.createTopology(TOPOLOGY_TYPE::TriangleList);

  /// RASTERIZER STATE
  SPtr<RasterizerState> p_rasterizer = nullptr;
  p_rasterizer = grapi.createRasterizerState(CULL_MODE::CULL_BACK,
                                             FILL_MODE::FILL_SOLID, true);
  if (!p_rasterizer)     {
    std::cout << "Failed to create rasterizer state" << std::endl;
    return -1;
  }

  /// TEXTURES
  SPtr<Texture2D>defaultNormalTexture = grapi.createTexture2DWithImageData(neutralNormal,
                                                                           1,
                                                                           1);

  SPtr<Texture2D>defaultSpecularTexture = grapi.createTexture2DWithImageData(whitePixel,
                                                                             1,
                                                                             1);

  SPtr<Texture2D>defaultAlbedoTexture = grapi.createTexture2DWithImageData(whitePixel,
                                                                           1,
                                                                           1);

  SPtr<Texture2D>cubeTexture = grapi.createTexture2DFromFile("RawData/Rocks.jpg");
  if (!cubeTexture) {
    std::cout << "Failed to load texture" << std::endl;
    return -1;
  }

  SPtr<Texture2D>cubeTex2 = grapi.createTexture2DFromFile("RawData/12.jpg");

  while (running) {
    window->processMessages();

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - pre;
    pre = now;

    time += elapsed.count();

    const float angle = time * 0.5f;
    const float cosine = Math::cos(angle);
    const float sine = Math::sin(angle);

    Matrix4 modelWorldRotation = Matrix4::fromRotationMatrix(
      1.0f, 0.0f, 0.0f,
      0.0f, cosine, sine,
      0.0f, -sine, cosine
    );

    Matrix4 modelWorld = modelWorldRotation * modelWorldScale;
    cameraData.worldMatrix = modelWorld;

    grapi.updateConstBuffer(p_constBufferCamera,
                            sizeof(GeneralConstBuffer),
                            &cameraData);

    grapi.setRenderTargetViews(gRenderTVS,
                               p_depthSV);

    grapi.clearRenderTargetView(p_swapChain->getRenderTargetView(),
                                semiClearColor);

    grapi.clearDepthStencilView(p_depthSV,
                                static_cast<ClearFlags::E>(flag),
                                1.0f,
                                0.0f);

    grapi.setRasterizerState(p_rasterizer);

    grapi.setVertexShader(p_vertexShader);
    grapi.setPixelShader(p_ShaderShader);
    //grapi.setPixelShader(p_pixelShader1);

    grapi.setSamplerState(0, p_sampler);

    grapi.setTopology(p_topology);

    grapi.setTexture2D(0,
                       defaultNormalTexture);
    grapi.setTexture2D(1,
                       cubeTexture ? cubeTexture : defaultAlbedoTexture);

    grapi.setTexture2D(2, defaultSpecularTexture);

    grapi.setVertexBuffer(
      p_vertexBuffer,
      sizeof(SimpleVertex),
      0
    );
    grapi.setIndexBuffer(p_indexBuffer);
    grapi.setConstBuffer(p_constBufferCamera);

    grapi.draw(
      static_cast<uint32>(cubeIndices.size()),
      0
    );

    Matrix4 translationMatrix = Matrix4::fromTranslationVector({ 75.f,75.f,75.f });
    modelWorld *= translationMatrix;
    cameraData.worldMatrix = modelWorld;

    grapi.updateConstBuffer(p_constBufferCamera,
                            sizeof(GeneralConstBuffer),
                            &cameraData);

    grapi.setTexture2D(1, cubeTex2);

    grapi.draw(
      static_cast<uint32>(cubeIndices.size()), 0);

    p_swapChain->present(1, 0);
  }

  grapi.cleanUpResources();
  GraphicsAPI::shutDown();
  return 0;
}
