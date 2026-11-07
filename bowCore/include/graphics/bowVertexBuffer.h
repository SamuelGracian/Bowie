/************************************************************************/
/**
 * @file bowVertexBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Genereic class of a base vertex buffer.
 */
 /*************************************************************************/
#pragma once

#include "bowBaseBuffer.h"

namespace bowEngineSDK
{
class VertexBuffer : public BaseBuffer
{
 public:

   /*
   * @brief
   *  Default constructor.
   */
   VertexBuffer(uint32 _byteWidth)
     : BaseBuffer(_byteWidth)
   {
     BOW_ASSERT(m_byteWidth != 0);
   }

   /*
   * @brief
   *  Default destructor.
   */
   ~VertexBuffer() = default;
};
}/// namespace bowEngineSDK
