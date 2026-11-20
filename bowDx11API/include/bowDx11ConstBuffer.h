/************************************************************************/
/**
 * @file bowDx11ConstBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 * DX11 implementation for const buffer.
 */
 /*************************************************************************/
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
   Dx11ConstBuffer(uint32 _byteWidth)
     : ConstBuffer(_byteWidth),
       m_buffer(nullptr)
   {}
  
  /*
  * @brief
  *  Default destructor.
  */
  ~Dx11ConstBuffer();
  
  /*
  * @brief
  *  Returns a pointer to the buffer.
  * @param none
  * @return ID3D11Buffer*
  */
  ID3D11Buffer* getBuffer();
  
  ID3D11Buffer* m_buffer;
};
}/// name space bowEngineSDK
