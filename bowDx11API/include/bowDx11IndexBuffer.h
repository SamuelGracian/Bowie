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
   Dx11IndexBuffer(uint32 _byteWidth)
     : IndexBuffer(_byteWidth),
       m_buffer (nullptr)
    {}

   /*
   * @brief
   *  Default destructor.
   */
   ~Dx11IndexBuffer() = default;


   ID3D11Buffer* m_buffer;
};
}/// namespace bowEngineSDK
