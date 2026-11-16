/************************************************************************/
/**
 * @file bowTopology.h
 * @author Samuel G
 * @date 26/10/2026
 * @brief
 *  Base class for topology.
 */
 /*************************************************************************/

#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class Topology
{

 public:

   /**
   * @brief
   * Default constructor.
   */
  Topology() 
    : m_type (TOPOLOGY_TYPE::kTriangleList)
  {}

  /**
  * @brief
  *  Default destructor.
  */
  virtual ~Topology() = default;

  /**
  * @brief
  *  Set the type.
  * @param type: new topology type.
  * @return none
  */
  FORCEINLINE void 
  setType(TOPOLOGY_TYPE::E _type) { m_type = _type; }

  /**
  * @brief
  *  Get the current type of the topology.
  * @param none
  * @return Current type.
  */
  FORCEINLINE TOPOLOGY_TYPE::E
  getType() const { return m_type; }

 protected:
  TOPOLOGY_TYPE::E m_type;

};
}/// name space bowEngineSDKs
