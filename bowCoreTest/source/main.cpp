#include "bowWindow.h"
#include "bowDx11GraphicsAPI.h"


using namespace bowEngineSDK;

int main() {
  bowEngineSDK::DisplaySurface window;

  window.init(800, 600, "Window test");

  GraphicsAPI::startUp<Dx11GraphicsAPI>();

  while (true) {
    window.processMessages();
  }
  return 0;
}
