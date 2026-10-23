#include "bowWindow.h"
#include "bowGraphicsAPI.h"


using namespace bowEngineSDK;

int main() {
  bowEngineSDK::DisplaySurface window;

  window.init(800, 600, "Window test");

  while (true) {
    window.processMessages();
  }
  return 0;
}
