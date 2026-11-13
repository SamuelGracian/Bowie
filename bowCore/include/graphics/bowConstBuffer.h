/************************************************************************/
/**
 * @file bowConstBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Base class for a constant buffer.
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
   ConstBuffer(uint32 _byteWidth, uint32 _slot)
     : BaseBuffer(_byteWidth),
       m_slot(_slot)
   {
     BOW_ASSERT(_slot < BUFFER_HIGHER_AVAILABLE_SLOT);
   }

   /*
   * @brief
   *  Default destructor.
   */
   ~ConstBuffer() = default;

   /*
   * @brief
   *  Returns the slot of the buffer.
   * @param none
   * @return UINT32
   *  Assigned slot for the buffer.
   */
   FORCEINLINE uint32
   getSlot() const {
     return m_slot;
   }

 protected:

   uint32 m_slot;
   void* m_rawData;
   bool m_isUpdatePending;
};
}/// name space bowwEngineSDK
