/************************************************************************/
/**
 * @file bowViewPort.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Base class for texture objects.
 */
 /*************************************************************************/

#pragma once 

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class ViewPort
{
 public:

  /**
  * @brief
  *  Default destructor.
  */
  ViewPort(float _width, float _height, float _minDepth,
           float _maxDepth, float _topLeftX, float _topLeftY)
    : width(_width), height(_height), minDepth(_minDepth),
    maxDepth(_maxDepth), topLeftX(_topLeftX), topLeftY(_topLeftY) 
  {}

  /**
  * @brief
  *  Default destructor.
  */
  virtual
  ~ViewPort() = default;

  float width;
  float height;
  float minDepth;
  float maxDepth; 
  float topLeftX;
  float topLeftY;
};
}/// name space BowEngineSDK
