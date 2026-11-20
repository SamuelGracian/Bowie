#pragma once 

#include "bowDx11Requisites.h"
#include "bowVertexBuffer.h"

namespace bowEngineSDK
{
class Dx11VertexBuffer : public VertexBuffer
{
  friend class Dx11GraphicsAPI;
 public:

   /*
   * @brief
   *  Constructor, sets the buffer as nullptr.
   */
   Dx11VertexBuffer(uint32 _byteWidth)
     : VertexBuffer(_byteWidth),
       m_buffer(nullptr)
  {}

  /*
  * @brief
  *  Default destructor.
  */
   FORCEINLINE
  ~Dx11VertexBuffer();

 protected:
  ID3D11Buffer* m_buffer;

};

Dx11VertexBuffer::~Dx11VertexBuffer() {
  safeRelease(m_buffer);
}
}/// name space bowEngineSDK
