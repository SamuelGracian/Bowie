/************************************************************************/
/**
 * @file bowConstBuffer.h
 * @author Samuel G
 * @date 23/10/2026
 * @brief
 *  Generic class of a depth stencil view object.
 */
 /*************************************************************************/
#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
  class DepthStencilView
  {
  public:
    /**
    * @brief
    *  Default constructor.
    */
    DepthStencilView() = default;

    /**
    * @brief
    *  Default destructor
    */
    virtual
    ~DepthStencilView() = default;
  };
  
}/// name space bowEngineSDK