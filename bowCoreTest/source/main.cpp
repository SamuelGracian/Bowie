#include "bowWindow.h"
#include "bowDx11GraphicsAPI.h"
#include "bowMath.h"

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

struct MoveVertex
{
  float cosValue;
  float amplitude;
  float c;
  float d;
};

int main() {
  //bowEngineSDK::DisplaySurface window;

  bool running = true;
  float handenes = -1.0f; /// 1.0 for right handed, -1.0 left handed
  float width = 800;
  float height = 600;

  /// Cameras
  Vector3 Eye(150.0f, 150.0f, 500.0f);
  Vector3 At(0.0f, 0.0f, 0.0f);
  Vector3 Up(0.0f, 1.0f, 0.0f);


  Matrix4 view = Matrix4::lookAt(At, Eye, Up, handenes);
  Matrix4 perspective = Matrix4::persepctive(Math::PI / 4.0f,
                                             (float) width / (float)height,
                                             0.01f,1000.0f, handenes);

  auto window = std::make_shared<DisplaySurface>();

  if (!window->init(width, height, "Window test")) {
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

  auto swapChain = grapi.createSwapChain(window,
                                         TEXTURE_FORMAT::R8G8B8A8_UNORM);

  if (!swapChain) {
    grapi.cleanUpResources();
    GraphicsAPI::shutDown();
    std::cout << "Failed to start swap chain" << std::endl;
    return -1;
  }

  /// Render target view
  auto renderTV = swapChain->getRenderTargetView();
 
  if (!renderTV) {
    std::cout << "Failed to create render target view " << std::endl;
  }

  ///const buffer for camera
  GeneralConstBuffer cameraData;
  cameraData.View = view;
  cameraData.Perspective = perspective;
  cameraData.cameraPosition = Eye;
  cameraData.Shininess = 2;


  Vector<SimpleVertex> cubeVertices {
    
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

  uint32 cubeIndexCount = 0;


  while (running) {
    window->processMessages();
  }
  grapi.cleanUpResources();
  GraphicsAPI::shutDown();
  return 0;
}
