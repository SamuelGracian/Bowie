/************************************************************************/
/**
 * @file bow3Dmodel.h
 * @author Samuel G
 * @date 21/11/2026
 * @brief
 *  3D model class.
 */
 /*************************************************************************/
#pragma once 

#include "bowCoreRequisites.h"
#include "bowVertexBuffer.h"
#include "bowIndexBuffer.h"
#include "bowVector2.h"
#include "bowVector4.h"


namespace bowEngineSDK
{

class Model3D
{
 public:
  /**
  * @brief 
  *  Default constructor, sets everything as 0 or nullptr.
  */
  Model3D() = default;

  /**
  * @brief
  *  Default destructor
  */
  ~Model3D();

  /**
  * @brief
  * Import the model using assimp
  * @praram
  * @return true if the model was imported correctly.
  */
  //bool
  //importModel(const String& fileName, Vector<uint16>& outIndices,
  //            Vector<SimpleVertex>&outVertex);

 private:

   VertexBuffer* m_vertexBuffer;
   IndexBuffer* m_indexBuffer;
};
}
