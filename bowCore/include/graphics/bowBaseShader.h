/************************************************************************/
/**
 * @file bowBaseShader.h
 * @author Samuel G
 * @date 23/10/2026
 * @brief
 *  Base class for shaders objects.
 */
 /*************************************************************************/

#pragma once

namespace bowEngineSDK
{
class BaseShader
{
 public:
   /*
   * @brief
   * Default constructor.
   */
   BaseShader() = default;

   /*
   * @brief
   * Default destructor.
   */
   virtual
   ~BaseShader() = default;
};
}
