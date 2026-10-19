#pragma once

#include "bowTexture2D.h"

namespace bowEngineSDK
{
class RenderTargetView : public Texture2D
{
 public:
   /*
   * @brief
   *  Default constructor.
   */
   RenderTargetView() = default;

   /*
   * @brief
   *  Default destructor.
   */
   ~RenderTargetView() = default;
};
}/// namespace bowEngineSDK
