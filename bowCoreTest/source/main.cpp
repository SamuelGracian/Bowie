#include "display/bowWindow.h"

using namespace bowEngineSDK;

int main() {
  bowEngineSDK::DisplaySurface window;
  UNICHAR windowName[] = u"Window test";
  window.init(800, 600, windowName);

  while (true) {
    window.processMessages();
  }
  return 0;
}
