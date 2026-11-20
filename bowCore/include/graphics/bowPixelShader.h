/************************************************************************/
/**
 * @file bowPixelShader.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Base class for pixel shaders.
 */
 /*************************************************************************/

#pragma once

#include "bowBaseShader.h"

namespace bowEngineSDK
{
class PixelShader : public BaseShader
{
 public:

   /*
   * @brief
   *  Default constructor.
   */
   PixelShader() = default;

   /*
   * @brief
   *  Default destructor.
   */
   ~PixelShader() = default;
};
}/// name space bowEngineSDK
