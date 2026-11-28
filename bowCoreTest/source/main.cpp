#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "bowComponent.h"
#include "bowActor.h"
#include "bowGraphicsAPI.h"
#include "bowRenderTargetView.h"
#include "bowMaterial.h"
#include "bowMath.h"
#include "bowMatrix.h"
//#include "bowModel.h"
#include "bowVector4.h"
#include "bowVector3.h"
#include "bowSwapChain.h"
#include "bowWindow.h"
#include "bowCube.h"

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
  constexpr float cameraSpeed = 15.0f;

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
  /* COLORS */
  float semiClearColor[4] = { 0.02f, 0.08f, 0.20f, 1.0f };
  /* FLAG */
  uint8 flag = CLEAR_FLAGS::kDepth | CLEAR_FLAGS::kStencil;

  Vector3 at(0.0f, 0.0f, 0.0f);
  Matrix4 perspective = Matrix4::perspective(Math::PI / 4.0f,
                                             width / height,
                                             0.01f, 1000.0f);


  /// INIT WINDOW
  auto window = makeShared<DisplaySurface>();

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
    std::cout << "Failed to init graphics api" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }

  /// SHADERS
  SPtr<PixelShader>p_shaderShader = grapi.createPixelShader(
                   readFileToString(L"RawData/shaders/pixelShaders/Shaders.fxh"),
                  "PShader",
                  defines,
                  4);
  if (!p_shaderShader)     {
    std::cout << "Failed to create shader" << std::endl;
    GraphicsAPI::shutDown();
    return-1;
  }

  SPtr<PixelShader>p_pixelShader1 = grapi.createPixelShader(
              readFileToString(L"RawData//shaders/pixelShaders/PixelShader.fxh"),
              "PShader",
              defines,
              4);
  if (!p_pixelShader1) {
    std::cout << "Failed to create pixel shader" << std::endl;
    GraphicsAPI::shutDown();
    return-1;
  }

  SPtr<VertexShader> p_vertexShader = grapi.createVertexShader(
    readFileToString(L"RawData//shaders/vertexShaders/VertexShader.fxh"),
    "VShader",
    defines,
    4);
  if (!p_vertexShader) {
    std::cout << "Failed to create vertex shader" << std::endl;
    GraphicsAPI::shutDown();
    return-1;
  }

  /// DEPTH STENCIL VIEW
  SPtr<DepthStencilView> p_depthSV =
    grapi.createDepthStencil(window->getClientWidth(),
                             window->getClientHeight(),
                             TEXTURE_FORMAT::kD24_UNORM_S8_UINT);

  /// SWAP CHAIN
  SPtr<SwapChain> p_swapChain = grapi.createSwapChain(window,
                                         TEXTURE_FORMAT::kR8G8B8A8_UNORM);

  if (!p_swapChain) {
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
  //cameraData.View = view;
  cameraData.Perspective = perspective;
  cameraData.worldMatrix = Matrix4::IDENTITY;
  cameraData.shadowView = Matrix4::IDENTITY;
  cameraData.shadowProjection = Matrix4::IDENTITY;
  //cameraData.cameraPosition = Eye;
  cameraData.Shininess = 2;

  SPtr<ConstBuffer> p_constBufferCamera = 
    grapi.createConstBuffer(sizeof(GeneralConstBuffer));

  if (!p_constBufferCamera) {
    BOW_LOG_ERROR("Failed to create camera const buffer" << std::endl);
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


  /// ASSIMP MODEL
  //Vector<Actor> actors;

  Actor pistolActor;

  pistolActor.hasComponent<Component>();
  //Model3D pistolModel;
  //if (!pistolModel.load("RawData/models/drakefire_pistol_low.obj")) {
  //  BOW_LOG_ERROR("Failed to load model" << std::endl);
  //  return -1;
  //}

  //if (!pistolModel.createBuffers()) {
  //  BOW_LOG_ERROR("Failed to create buffers" << std::endl);
  //  return -1;
  //}

  ////pistolActor.model = pistolModel;

  //std::cout << "Vertices" << pistolModel.getVertices().size()
  //  << " , Indices" << pistolModel.getIndexCount()
  //  << std::endl;

  ////pistolActor.material.loadTexture({
  //// { MATERIAL_TEXTURES::kNormal,"RawData/Textures/base_normal.jpg" },
  //// { MATERIAL_TEXTURES::kAlbedo, "RawData/Textures/drakefire_pistol_low_a.jpg" },
  //// { MATERIAL_TEXTURES::kSpecular, "RawData/Textures/base_metallic.jpg"}
  ////                                  });

  ////pistolActor.worldMatrix = Matrix4::IDENTITY;

  //actors.push_back(pistolActor);

  //AAB boundingBox = pistolModel.getBoundingBox(); /// Pistol's bounding box
  //Vector3 lookingAt = boundingBox.getCenter();
  //Vector3 eye = lookingAt - Vector3(0.0f, 0.0f, boundingBox.getSize().z + 5);
  //Matrix4 view;

  ///// rex model
  //Actor rexActor;

  //rexActor.hasComponent <Vector3> ();
  //Model3D rexModel;
  //if (!rexModel.load("RawData/models/rex_norm.obj")) {
  //  BOW_LOG_ERROR("Failed to load model" << std::endl);
  //  return -1;
  //}

  //if (!rexModel.createBuffers()) {
  //  BOW_LOG_ERROR("Failed to create buffers" << std::endl);
  //  return -1;
  //}

  //rexActor.model = rexModel;

  //SPtr<Texture2D> rexTexture = grapi.createTexture2DFromFile("RawData/textures/Rex_C.bmp");

  //rexActor.material.setTexture(MATERIAL_TEXTURES::kNormal,
  //                             defaultNormalTexture);

  //rexActor.material.setTexture(MATERIAL_TEXTURES::kAlbedo,
  //                             rexTexture);

  //rexActor.material.setTexture(MATERIAL_TEXTURES::kSpecular,
  //                             defaultSpecularTexture);

  //rexActor.worldMatrix = 
  //  Matrix4::IDENTITY * Matrix4::fromTranslationVector(Vector3(3.0f, 3.0f, 3.0f));

  //actors.push_back(rexActor);

  /// RASTERIZER STATE
  SPtr<RasterizerState> p_rasterizer = nullptr;
  p_rasterizer = grapi.createRasterizerState(CULL_MODE::kCULL_BACK,
                                             FILL_MODE::kFILL_SOLID, true);
  if (!p_rasterizer)     {
    std::cout << "Failed to create rasterizer state" << std::endl;
    GraphicsAPI::shutDown();
    return -1;
  }


  while (running == true) {
    if (!window->processMessages()) {
      running = false;
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - pre;
    pre = now;

    //const float deltaTime = elapsed.count();

    /*updateCameraInput(deltaTime,
                      eye,
                      lookingAt,
                      Vector3::UP);*/

    //view = Matrix4::lookAt(eye, lookingAt, Vector3::UP);
    //cameraData.View = view;
    //cameraData.cameraPosition = eye;

    grapi.updateConstBuffer(
      p_constBufferCamera,
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
    grapi.setPixelShader(p_shaderShader);

    grapi.setSamplerState(0, p_sampler);
    

    grapi.setVertexShader(p_vertexShader);
    grapi.setPixelShader(p_shaderShader);
    grapi.setTopology(TOPOLOGY_TYPE::kTriangleList);


    /*for (const Actor& actor : actors) {
      /// set material
      actor.material.setMaterial();

      /// actor transform
      cameraData.worldMatrix = actor.worldMatrix;
      grapi.updateConstBuffer(p_constBufferCamera,
                              sizeof(GeneralConstBuffer),
                              &cameraData);
      grapi.setConstBuffer(p_constBufferCamera, 0);

      /// set model buffers
      grapi.setVertexBuffer(actor.model.getVertexBuffer(), sizeof(ModelVertex), 0);
      grapi.setIndexBuffer(actor.model.getIndexBuffer(), TEXTURE_FORMAT::kR16_UINT);

      grapi.drawIndexed(actor.model.getIndexCount(), 0);
    }*/
    p_swapChain->present(1, 0);
    
  }
    GraphicsAPI::shutDown();
    return 0;
  
}
