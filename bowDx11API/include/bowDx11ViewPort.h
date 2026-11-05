#pragma once
#include "bowViewPort.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11ViewPort :public ViewPort
{
 public:
  Dx11ViewPort(float _width, float _height,
               float _minDepth, float _maxDepth,
               float _topLeftX, float _topLeftY)
    : ViewPort(_width, _height,
               _minDepth, _maxDepth,
               _topLeftX, _topLeftY),
    m_viewPort {} {
    m_viewPort.Width = _width;
    m_viewPort.Height = _height;
    m_viewPort.MinDepth = _minDepth;
    m_viewPort.MaxDepth = _maxDepth;
    m_viewPort.TopLeftX = _topLeftX;
    m_viewPort.TopLeftY = _topLeftY;
   }
  ~Dx11ViewPort() = default;
  
  D3D11_VIEWPORT m_viewPort;
};
}/// namespace BowEngineSDK
