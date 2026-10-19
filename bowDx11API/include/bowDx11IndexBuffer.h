#pragma once 
#include "bowDx11Requisites.h"

#include "bowIndexbuffer.h"

namespace bowEngineSDK
{
class Dx11IndexBuffer : public Indexbuffer
{
 public:

   /*
   * @brief
   *  Constructor, sets the buffer as nullptr.
   */
   Dx11IndexBuffer()
     : m_buffer (nullptr)
   {}

   /*
   * @brief
   *  Default destructor.
   */
   ~Dx11IndexBuffer() = default;

 private:
   ID3D11Buffer* m_buffer;
};
}/// namespace bowEngineSDK
