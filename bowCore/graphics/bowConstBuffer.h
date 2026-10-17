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

#define HIGHER_AVAILABLE_SLOT 8

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
   void
   setSlot(const uint32 slot);

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
   static constexpr uint32 HIGHER_AVAILABLE_SLOT = 8;
   uint32 m_slot;
   void* m_rawData;
   bool m_isUpdatePending;
};
}/// namespace bowwEngineSDK
