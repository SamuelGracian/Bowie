#include "bowConstBuffer.h"

namespace bowEngineSDK
{
void
ConstBuffer::setSlot(uint32 _slot) {
  BOW_ASSERT(_slot < BUFFER_HIGHER_AVAILABLE_SLOT);
  m_slot = _slot;
}
}/// namespace bowEngineSDK
