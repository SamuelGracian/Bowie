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
  /*
  * @brief
  *  Default constructor.
  * @param _byteWidth, byteWidth of the buffer.
  */
 public:
  explicit
  BaseBuffer(uint32 _byteWidth) 
    : m_byteWidth(_byteWidth)
  {
    BOW_ASSERT(m_byteWidth != 0);
  }

  /*
  * @brief
  *  Default destructor.
  */
  virtual
  ~BaseBuffer() = default;

  /*
  * @brief
  *  Gets the byteWidth of the buffer.
  * @param none
  * @return 
  */
  NODISCARD FORCEINLINE uint32
  getByteWidth() const { return m_byteWidth; }

 protected:
  uint32 m_byteWidth;
};
}/// name space bowEngineSDK
