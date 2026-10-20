#include "bowDx11ConstBuffer.h"

namespace bowEngineSDK
{
Dx11ConstBuffer::Dx11ConstBuffer() 
  : m_buffer(nullptr)
{}

ID3D11Buffer*
Dx11ConstBuffer::getBuffer() {
  return m_buffer;
}

}