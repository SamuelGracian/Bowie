/************************************************************************/
/**
 * @file bowIndexBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Generic class of a base buffer.
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
