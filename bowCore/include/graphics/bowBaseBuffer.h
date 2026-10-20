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
  BaseBuffer() = default;
  ~BaseBuffer() = default;

  void 
  SetByteWidth(const uint32 bytewidth = 0) {
    assert(bytewidth != 0);
    m_byteWidth = bytewidth;
  }

  FORCEINLINE const uint32
  GetByteWidth()const { return m_byteWidth; }

 protected:
  uint32 m_byteWidth;
};
}/// namespace bowEngineSDK
