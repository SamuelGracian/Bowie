/************************************************************************/
/**
 * @file bowTexture2D.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Base class for texture objects.
 */
 /*************************************************************************/

#pragma once

#include "bowGraphicsGenerals.h"

namespace bowEngineSDK
{
class Texture2D
{
 public:

   /*
   * @brief
   *  Default destructor.
   */
   virtual ~Texture2D() = default;

 protected:
   uint32 m_width = 0;
   uint32 m_height = 0;
   TEXTURE_FORMAT::E m_format = TEXTURE_FORMAT::kFORMAT_UNKNOWN;

};
}/// name space bowEngineSDK
