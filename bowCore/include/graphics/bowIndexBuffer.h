/************************************************************************/
/**
 * @file bowIndexBuffer.h
 * @author Samuel G
 * @date 18/10/2026
 * @brief
 *  Base class for a Index Buffer.
 */
 /*************************************************************************/

#pragma once

#include "bowBaseBuffer.h"

namespace bowEngineSDK
{
class IndexBuffer :public BaseBuffer
{
 public:

   /*
   * @brief
   *  Default constructor
   */
   IndexBuffer(uint32 _byteWidth)
     : BaseBuffer(_byteWidth) 
   {
     BOW_ASSERT(m_byteWidth != 0);
   }

   /*
   * @brief
   *  Default destructor
   */
   ~IndexBuffer() = default;
};
}/// name space bowEngineSDK
