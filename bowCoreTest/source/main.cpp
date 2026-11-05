#include "bowWindow.h"
#include "bowDx11GraphicsAPI.h"
#include "bowMatrix.h"
#include "bowVector4.h"
#include "bowVector3.h"

using namespace bowEngineSDK;


struct GeneralConstBuffer
{
  Matrix4 View;
  Matrix4 Perspective;
  Matrix4 worldMatrix;
  Matrix4 ShadowView;
  Matrix4 ShadowProjection;
  Vector4 cameraPosition;
  float Shininess;
};

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
  Vector4 texture;

  SimpleVertex(
    Vector4& pos,
    Vector4& normal,
    Vector4& tan,
    Vector4& binormal,
    Vector4& tex)
    : position(pos), normals(normal), tangent(tan), binormals(binormal),
    texture(tex) {}
};/// Simple vertex struct

int main() {
  //bowEngineSDK::DisplaySurface window;

  bool running = true;

  /// Cameras
  Vector3 Eye(100.0f, 100.0f, 500.0f);
  Vector3 At(0.0f, 0.0f, 0.0f);
  Vector3 Up(0.0f, 1.0f, 0.0f);


  auto window = std::make_shared<DisplaySurface>();

  if (!window->init(800, 600, "Window test")) {
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
  SPtr<RenderTargetView> renderTV = swapChain->getRenderTargetView();
 
  if (!renderTV) {
    std::cout << "Failed to create render target view " << std::endl;
  }

  ///const buffer for camera
  float amplitude = 0.0f;
  MoveVertex moveData = { 1.0, amplitude, 1.0f,1.0 };
  //GeneralConstBuffer cameraData;
  //cameraData.View = view

  while (running) {
    window->processMessages();
  }
  grapi.cleanUpResources();
  GraphicsAPI::shutDown();
  return 0;
}
