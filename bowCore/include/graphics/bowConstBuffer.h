/************************************************************************/
/**
 * @file bowConstBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Genereic class of a base buffer.
 */
 /*************************************************************************/
#pragma once 

#include "bowBaseBuffer.h"
#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class ConstBuffer : public BaseBuffer
{
 public:

   /*
   * @brief
   *  Default constructor.
   */
   ConstBuffer() = default;

   /*
   * @brief
   *  Default destructor.
   */
   ~ConstBuffer() = default;

   /*
   * @brief
   *  Set the slot of the buffer.
   * @param UINT32
   *  Slot where the buffer is going to be assign.
   * @return NONE
   */
   FORCEINLINE void
   setSlot(const uint32 _slot) {
     BOW_ASSERT(_slot < BUFFER_HIGHER_AVAILABLE_SLOT);
     m_slot = _slot;
   }

   /*
   * @brief
   *  Returns the slot of the buffer.
   * @param NONE
   * @return UINT32
   *  Assigned slot for the buffer.
   */
   FORCEINLINE uint32
   getSlot() const {
     return m_slot;
   }

 private:

   uint32 m_slot;
   void* m_rawData;
   bool m_isUpdatePending;
};
}/// namespace bowwEngineSDK
