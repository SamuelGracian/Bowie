#include "bowDx11ConstBuffer.h"

namespace bowEngineSDK
{
Dx11ConstBuffer::Dx11ConstBuffer() 
  : m_buffer(nullptr)
{}

Dx11ConstBuffer::getBuffer() {
  return m_buffer;
}

}