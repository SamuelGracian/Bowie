#pragma once 

#include "bowBaseBuffer.h"

#define HIGHER_AVAILABLE_SLOT 8

namespace bowEngineSDK
{
class ConstBuffer : public BaseBuffer
{
 public:
   ConstBuffer() = default;

   ~ConstBuffer() = default;

   void
   setSlot(const uint32 slot);

   FORCEINLINE uint32
    getSlot() const

 private:
   static constexpr uint32 HIGHER_AVAILABLE_SLOT  = 8
};
}/// namespace bowwEngineSDK
