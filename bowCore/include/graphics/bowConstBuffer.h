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
   ConstBuffer(uint32 _byteWidth)
     : BaseBuffer(_byteWidth)
   {
   }

   /*
   * @brief
   *  Default destructor.
   */
   ~ConstBuffer() = default;

};

}/// name space bowwEngineSDK
