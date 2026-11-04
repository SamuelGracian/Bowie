#include "bowWindow.h"
#include "bowDx11GraphicsAPI.h"


using namespace bowEngineSDK;

int main() {
  //bowEngineSDK::DisplaySurface window;

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

  bool running = true;

  while (running) {
    window->processMessages();
  }
  grapi.cleanUpResources();
  GraphicsAPI::shutDown();
  return 0;
}
