#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>

#include "bowGraphicsAPI.h"
#include "bowRenderTargetView.h"
#include "bowMath.h"
#include "bowMatrix.h"
#include "bowVector4.h"
#include "bowVector3.h"
#include "bowSwapChain.h"
#include "bowWindow.h"

#include "bowDynamicLibrary.h"

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

Vector<String> defines { "#define BOWIE_TEST" };
Vector<uint8_t> neutralNormal = { 127, 127, 255, 255 };
Vector<uint8_t> whitePixel = { 255, 255, 255, 255 };

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
readFileToString(const WString& _filePath) {
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

void updateCameraInput(float deltaTime,
                       Vector3& eye,
                       Vector3& at,
                       const Vector3& up) {
  constexpr float cameraSpeed = 150.0f;

  Vector3 forward = at - eye;
  forward.y = 0.0f;

  if (forward.sqrMagnitude() <= PlatformMath::KINDA_SMALL_NUMBER) {
    return;
  }

  forward = forward.normalize();

  Vector3 right = forward.cross(up);

  if (right.sqrMagnitude() <= PlatformMath::KINDA_SMALL_NUMBER) {
    return;
  }

  right = right.normalize();

  Vector3 movement(0.0f, 0.0f, 0.0f);

  if ((GetAsyncKeyState('W') & 0x8000) != 0) {
    movement = movement + forward;
  }

  if ((GetAsyncKeyState('S') & 0x8000) != 0) {
    movement = movement - forward;
  }

  if ((GetAsyncKeyState('D') & 0x8000) != 0) {
    movement = movement + right;
  }

  if ((GetAsyncKeyState('A') & 0x8000) != 0) {
    movement = movement - right;
  }

  if (movement.sqrMagnitude() <= PlatformMath::KINDA_SMALL_NUMBER) {
    return;
  }

  movement = movement.normalize();

  eye = eye + movement * cameraSpeed * deltaTime;

  at = eye + forward;
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
  uint8 flag = CLEAR_FLAGS::kDepth | CLEAR_FLAGS::kStencil;

  /// Cameras
  Vector3 Eye(150.0f, 150.0f, 500.0f);
  Vector3 At(0.0f, 0.0f, 0.0f);
  Vector3 Up(0.0f, 1.0f, 0.0f);


  Matrix4 view = Matrix4::lookAt(Eye, At, Up);
  Matrix4 perspective = Matrix4::perspective(Math::PI / 4.0f,
                                             width / height,
                                             0.01f,1000.0f);

  /// WORLD MATRIX AND TRANSLATIONS
  Matrix4 modelWorldScale = Matrix4::fromScaleVector(Vector3(50, 50, 50));
  Vector3 modelWorldTranslation(0.0f, 0.0f, 0.0f);

  /// INIT WINDOW
  auto window = std::make_shared<DisplaySurface>();

  if (!window->init(static_cast<int32>(width), static_cast<int32>(height),
                    "Bowie")) {

    std::cout << "Failed to start window" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }

  using LoadPluginFunction = void (*)();
  DynamicLibrary plugin("bowDx11API.dll");
  
  if (!plugin.load()) {
    std::cout << "Failed to load library" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }
  
  auto loadPlug = plugin.getSymbol<LoadPluginFunction>("loadPlugin");
  
  if (loadPlug == nullptr) {
    std::cout << "Failed to find plugin" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }

  loadPlug();

  GraphicsAPI& grapi = GraphicsAPI::instance();

  /// WINDOW
  if (!grapi.init(window)) {
    GraphicsAPI::shutDown();
    std::cout << "Failed to init graphics api" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }

  /// SHADERS
  SPtr<PixelShader>p_ShaderShader = grapi.createPixelShader(
                                     readFileToString(L"RawData/Shaders.fxh"),
                                     "PShader",
                                     defines,
                                     4);
  if (!p_ShaderShader)     {
    std::cout << "Failed to create shader" << std::endl;
    return-1;
  }

  SPtr<PixelShader>p_pixelShader1 = grapi.createPixelShader(
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
                                                              TEXTURE_FORMAT::kD24_UNORM_S8_UINT);

  /// SWAP CHAIN
  SPtr<SwapChain> p_swapChain = grapi.createSwapChain(window,
                                         TEXTURE_FORMAT::kR8G8B8A8_UNORM);

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
    GraphicsAPI::shutDown();
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
    grapi.createConstBuffer(sizeof(GeneralConstBuffer));

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
  SPtr <Topology> p_topology = grapi.createTopology(TOPOLOGY_TYPE::kTriangleList);

  /// RASTERIZER STATE
  SPtr<RasterizerState> p_rasterizer = nullptr;
  p_rasterizer = grapi.createRasterizerState(CULL_MODE::kCULL_BACK,
                                             FILL_MODE::kFILL_SOLID, true);
  if (!p_rasterizer)     {
    std::cout << "Failed to create rasterizer state" << std::endl;
    GraphicsAPI::shutDown();
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
    GraphicsAPI::shutDown();
    return -1;
  }

  SPtr<Texture2D>cubeTex2 = grapi.createTexture2DFromFile("RawData/12.jpg");

  while (running == true ) {
    if (!window->processMessages()) {
      running = false;
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - pre;
    pre = now;

    const float deltaTime = elapsed.count();
    time += elapsed.count();

    updateCameraInput(deltaTime, Eye, At, Up);

    view = Matrix4::lookAt(Eye, At, Up);
    cameraData.View = view;
    cameraData.cameraPosition = Eye;

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
                                static_cast<CLEAR_FLAGS::E>(flag),
                                1.0f,
                                0);

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
    grapi.setIndexBuffer(p_indexBuffer, TEXTURE_FORMAT::kR16_UINT);
    grapi.setConstBuffer(p_constBufferCamera, 0);

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
