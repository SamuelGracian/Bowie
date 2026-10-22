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
   *  Cosntructor, sets the buffer as nullptr.
   */
  Dx11VertexBuffer ()
    : m_buffer(nullptr)
  {}

  /*
  * @brief
  *  Default destructor.
  */
  ~Dx11VertexBuffer() = default;

 //private:
   ID3D11Buffer* m_buffer;

};
}/// namespace bowEngineSDK
