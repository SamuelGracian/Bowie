/************************************************************************/
/**
 * @file bowBasebuffer.h
 * @author Samuel G
 * @date 15/10/2026
 * @brief
 *  Base class for buffers.
 */
 /*************************************************************************/
#pragma once

#include "bowCoreRequisites.h"
#include "bowGraphicsGenerals.h"

namespace bowEngineSDK
{
class BaseBuffer
{
 public:
  BaseBuffer(uint32 _byteWidth) 
    : m_byteWidth(_byteWidth)
  {
    BOW_ASSERT(m_byteWidth != 0);
  }

  ~BaseBuffer() = default;

  FORCEINLINE NODISCARD uint32
  getByteWidth() const { return m_byteWidth; }

 protected:
  uint32 m_byteWidth;
};
}/// namespace bowEngineSDK
