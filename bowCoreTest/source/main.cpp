#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

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
  Matrix4 ShadowView;
  Vector3 cameraPosition;
  float Shininess;
};

Vector<String> defines { "#defines BOWIE_TEST" };

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
  //bowEngineSDK::DisplaySurface window;

  bool running = true;
  float width = 800;
  float height = 600;

  /// Cameras
  Vector3 Eye(150.0f, 150.0f, 500.0f);
  Vector3 At(0.0f, 0.0f, 0.0f);
  Vector3 Up(0.0f, 1.0f, 0.0f);


  Matrix4 view = Matrix4::lookAt(At, Eye, Up);
  Matrix4 perspective = Matrix4::perspective(Math::PI / 4.0f,
                                             width / height,
                                             0.01f,1000.0f);

  auto window = std::make_shared<DisplaySurface>();

  if (!window->init(static_cast<int32>(width),static_cast<int32>(height),
                    "Bowie")) {

    std::cout << "Failed to start window" << std::endl;
    return -1;
  }

  GraphicsAPI::startUp<Dx11GraphicsAPI>();

  GraphicsAPI& grapi = GraphicsAPI::instance();

  if (!grapi.init(window)) {
    GraphicsAPI::shutDown();
    std::cout << "Failed to init grapi" << std::endl;
    return -1;
  }

  if (SPtr<PixelShader> p_pixelShader = grapi.createPixelShader(
    readFileToString(L"RawData/Shaders.fxh"), "PShader", defines, 4)) {
    std::cout << "Shader Created " << std::endl;
  }

  SPtr<PixelShader> p_pixelShader1 = grapi.createPixelShader(
    readFileToString(L"RawData/PixelShader.fxh"),"PShader", defines, 4);

  SPtr<VertexShader> p_vertexShader = grapi.createVertexShader(
    readFileToString(L"RawData/VertexShader.fxh"), "VShader", defines, 4);

  SPtr<SwapChain> swapChain = grapi.createSwapChain(window,
                                         TEXTURE_FORMAT::R8G8B8A8_UNORM);

  if (!swapChain) {
    grapi.cleanUpResources();
    GraphicsAPI::shutDown();
    std::cout << "Failed to start swap chain" << std::endl;
    return -1;
  }

  /// Render target view
  SPtr<RenderTargetView> renderTV = swapChain->getRenderTargetView();
 
  if (!renderTV) {
    std::cout << "Failed to create render target view " << std::endl;
  }

  ///const buffer for camera
  //float amplitude = 0.0f;
  //MoveVertex moveData = { 1.0, amplitude, 1.0f,1.0 };
  //GeneralConstBuffer cameraData;
  //cameraData.View = view
  GeneralConstBuffer cameraData;
  cameraData.View = view;
  cameraData.Perspective = perspective;
  cameraData.cameraPosition = Eye;
  cameraData.Shininess = 2;

  /// CUBE OBJECTS
  Vector<SimpleVertex> cubeVertices {
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
                                            static_cast<uint32>(cubeVertices.size()),
                                            cubeVertices.data());

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



  while (running) {
    window->processMessages();
  }
  grapi.cleanUpResources();
  GraphicsAPI::shutDown();
  return 0;
}
