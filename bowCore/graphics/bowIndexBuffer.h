/************************************************************************/
/**
 * @file bowIndexBuffer.h
 * @author Samuel G
 * @date 16/10/2026
 * @brief
 *  Genereic class of a base buffer.
 */
 /*************************************************************************/

#pragma once

#include "bowBaseBuffer.h"

namespace bowEngineSDK
{
class Indexbuffer :public BaseBuffer
{
 public:

   /*
   * @brief
   *  Default constructor
   */
   Indexbuffer() = default;

   /*
   * @brief
   *  Defualt destructor
   */
   ~Indexbuffer() = default;
};
}/// namespace bowEngineSDK
