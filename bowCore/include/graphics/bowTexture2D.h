/************************************************************************/
/**
 * @file bowTexture2D.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Genereic class of a base buffer.
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
   TEXTURE_FORMAT::E m_format = TEXTURE_FORMAT::FORMAT_UNKNOWN;

};
}/// namespace bowEngineSDK
