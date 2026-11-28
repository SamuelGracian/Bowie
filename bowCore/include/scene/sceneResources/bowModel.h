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
#include "bowCube.h"
#include "bowVector2.h"
#include "bowVector4.h"

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

class IndexBuffer;
class VertexBuffer;

class Model3D
{
 public:
  ///**
  //* @brief 
  //*  Default constructor, sets everything as 0 or nullptr.
  //*/
   Model3D() : m_boundingBox(AAB(Vector3::ZERO, Vector3::ZERO)) {};

  ///**
  //* @brief
  //*  Default destructor
  //*/
  BOW_CORE_EXPORT
  ~Model3D();

  /**
  * @brief
  * Import the model using assimp
  * @praram
  * @return true if the model was imported correctly.
  */
  BOW_CORE_EXPORT
  bool
  load(const String& fileName);

  BOW_CORE_EXPORT
  bool
  isValid() const;

  BOW_CORE_EXPORT
  uint32
  getIndexCount()const;

  const
  BOW_CORE_EXPORT
  Vector<ModelVertex>&
  getVertices()const;

  BOW_CORE_EXPORT
  bool
  createBuffers();

  BOW_CORE_EXPORT
  SPtr<VertexBuffer>
  getVertexBuffer()const;

  BOW_CORE_EXPORT
  SPtr<IndexBuffer>
  getIndexBuffer()const;

  NODISCARD
  BOW_CORE_EXPORT
  FORCEINLINE
  AAB
  getBoundingBox()const {
    return m_boundingBox;
  }

 private:
  void
  calculateBoundingBox();

 private:
   AAB m_boundingBox;
   Vector<ModelVertex> m_vertices;
   Vector<uint16> m_indices;
   SPtr<VertexBuffer> m_vertexBuffer;
   SPtr<IndexBuffer> m_indexBuffer;
};
}
