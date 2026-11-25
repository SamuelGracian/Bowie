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
#include "bowGraphicsAPI.h"


namespace bowEngineSDK
{

struct ModelVertex
{
  Vector4 position;
  Vector4 normals;
  Vector4 tangents;
  Vector4 binormals;
  Vector2 texture;
};

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
  bool
  load(const String& fileName);

  bool
  isValid() const;

  uint32
  getIndexCount()const;

  const
  Vector<ModelVertex>&
  getVertices()const;

  bool
  createBuffers(GraphicsAPI& grapi);

  SPtr<VertexBuffer>
  getVertexBuffer()const;

  SPtr<IndexBuffer>
  getIndexBuffer()const;

 private:
   Vector<ModelVertex> m_vertices;
   Vector<uint16> m_indices;
   SPtr<VertexBuffer> m_vertexBuffer;
   SPtr<IndexBuffer> m_indexBuffer;
};
}
