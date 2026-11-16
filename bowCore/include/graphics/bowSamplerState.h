/************************************************************************/
/**
 * @file bowRasterizerState.h
 * @author Samuel G
 * @date 24/10/2026
 * @brief
 *  Base class for sampler states.
 */
 /*************************************************************************/
#pragma once

namespace bowEngineSDK
{
class SamplerState
{
 public:

  /**
  * @brief
  *  Default constructor.
  */
  explicit
  SamplerState() = default;

  /**
  * @brief
  *  Default destructor.
  */
  virtual
  ~SamplerState() = default;
};
}/// name space BowEngineSDK
