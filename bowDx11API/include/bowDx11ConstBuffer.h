#pragma once

#include "bowDx11Requisites.h"

#include "bowConstBuffer.h"

namespace bowEngineSDK
{
class Dx11ConstBuffer : public ConstBuffer
{
 public:
   /*
   * @brief
   *  Constructor, sets the buffer pointer as null.
   */
   Dx11ConstBuffer();

   /*
   * @brief
   *  Default destructor.
   */
   ~Dx11ConstBuffer() = default;

   /*
   * @brief
   *  Returns a pointer to the buffer.
   * @param NONE
   * @return ID3D11Buffer*
   */
   ID3D11Buffer* getBuffer();

 
   ID3D11Buffer* m_buffer;
};
}/// namespace bowEngineSDK
