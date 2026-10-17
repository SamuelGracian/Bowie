#include "bowConstbuffer.h"

namespace bowEngineSDK
{
void
ConstBuffer::setSlot(uint32 _slot) {
  MI_ASSERT(_slot < HIGHER_AVAILABLE_SLOT);
  m_slot = _slot;
}
}/// namespace bowEngineSDK
