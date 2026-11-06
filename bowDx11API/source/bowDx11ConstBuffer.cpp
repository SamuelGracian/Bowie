#include "bowDx11ConstBuffer.h"

namespace bowEngineSDK
{

ID3D11Buffer*
Dx11ConstBuffer::getBuffer() {
  return m_buffer;
}

}