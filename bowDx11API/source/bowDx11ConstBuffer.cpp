#include "bowDx11ConstBuffer.h"

namespace bowEngineSDK
{
Dx11ConstBuffer::~Dx11ConstBuffer() {
  safeRelease(m_buffer);
  m_slot = 0;
  m_rawData = nullptr;
}

ID3D11Buffer*
Dx11ConstBuffer::getBuffer() {
  return m_buffer;
}

}