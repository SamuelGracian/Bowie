
#include <iostream>

#if BOW_PLATFORM == BOW_PLATFORM_WIN32
#include <Windows.h>
#include "bowWindow.h"
#endif

namespace bowEngineSDK
{

#if BOW_PLATFORM == BOW_PLATFORM_WIN32
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
}
#endif 

DisplaySurface::~DisplaySurface() {
#if BOW_PLATFORM == BOW_PLATFORM_WIN32
  DestroyWindow(reinterpret_cast<HWND> (handler));
#endif
}


bool DisplaySurface::init(int32 _width, int32 _height, UNICHAR* windowName) {
  width = width;
  height = height;

#if BOW_PLATFORM == BOW_PLATFORM_WIN32
  const char CLASS_NAME[] = "DX11WindowClass";
  WNDCLASSEX wc {};
  wc.cbSize = sizeof(wc);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.lpszClassName = CLASS_NAME;
  RegisterClassEx(&wc);

  HWND hwnd = CreateWindowEx(
    0,
    CLASS_NAME,
    "Tecnicas Progra",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    width, height,
    nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

  if (!hwnd) {
    std::cout << "Window could not be created" << std::endl;
    return false;
  }

  RECT rc;
  GetClientRect(hwnd, &rc);
  clientWidth = rc.right - rc.left;
  clientHeight = rc.bottom - rc.top;

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);

  return true;
#else
  return false;
#endif
}

void DisplaySurface::processMessages() {
#if BOW_PLATFORM == BOW_PLATFORM_WIN32
  MSG msg {};
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
#endif
}
}// namespace bowEngineSDK
