#pragma once 

#include "bowDx11Requisites.h"
#include "bowVertexBuffer.h"

namespace bowEngineSDK
{
class Dx11VertexBuffer : public VertexBuffer
{
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
  ~Dx11VertexBuffer() = default;

   ID3D11Buffer* m_buffer;

};
}/// name space bowEngineSDK
