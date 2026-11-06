#pragma once 

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class ViewPort
{
public:
  ViewPort(float _width, float _height, float _minDepth,
           float _maxDepth, float _topLeftX, float _topLeftY)
    : width(_width), height(_height), minDepth(_minDepth),
    maxDepth(_maxDepth), topLeftX(_topLeftX), topLeftY(_topLeftY) 
  {}

  ~ViewPort() = default;

  float width;
  float height;
  float minDepth;
  float maxDepth; 
  float topLeftX;
  float topLeftY;
};
}/// namespace BowEngineSDK
