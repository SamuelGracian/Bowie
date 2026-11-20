/************************************************************************/
/**
 * @file bowDx11IndexBuffer.h
 * @author Samuel G
 * @date 18/10/2026
 * @brief
 * Dx11 implementation for index buffer.
 */
 /*************************************************************************/
#pragma once 
#include "bowDx11Requisites.h"

#include "bowIndexBuffer.h"

namespace bowEngineSDK
{
class Dx11IndexBuffer : public IndexBuffer
{
 public:

  /*
  * @brief
  *  Constructor, sets the buffer as nullptr.
  */
  explicit
  Dx11IndexBuffer(uint32 _byteWidth)
    : IndexBuffer(_byteWidth),
      m_buffer (nullptr)
   {}

  /*
  * @brief
  *  Default destructor.
  */
  FORCEINLINE
  ~Dx11IndexBuffer();

  ID3D11Buffer* m_buffer;
};

Dx11IndexBuffer::~Dx11IndexBuffer(){
  safeRelease(m_buffer);
}
}/// name space bowEngineSDK
