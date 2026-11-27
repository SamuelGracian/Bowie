#include "bowModel.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "bowGraphicsAPI.h"

namespace bowEngineSDK
{
Model3D::~Model3D() {
  if (m_indexBuffer) {
    m_indexBuffer = nullptr;
  }
  if (m_vertexBuffer) {
    m_vertexBuffer = nullptr;
  }
  }

bool
Model3D::load(const String& fileName) {

  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(
    fileName,
    aiProcess_Triangulate |
    aiProcess_FlipUVs |
    aiProcess_JoinIdenticalVertices |
    aiProcess_CalcTangentSpace |
    aiProcess_MakeLeftHanded);

  if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
    BOW_LOG_ERROR( "Error loading model: " << importer.GetErrorString() << std::endl);
    return false;
  }

  //for (unsigned int meshIndex = scene->mNumMeshes -1 ; meshIndex != 0; meshIndex--)
  for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
    aiMesh* mesh = scene->mMeshes[meshIndex];
    if (!mesh)
      continue;

    const uint32_t vertexOffset = static_cast<uint32_t>(m_vertices.size());

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
      ModelVertex vertex;
      vertex.position = Vector4(
        mesh->mVertices[i].x,
        mesh->mVertices[i].y,
        mesh->mVertices[i].z,
        1.0f);

      if (mesh->HasNormals() && mesh->mNormals) {
        vertex.normals = Vector4(
          mesh->mNormals[i].x,
          mesh->mNormals[i].y,
          mesh->mNormals[i].z,
          0.0f);
      }
      else {
        vertex.normals = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
      }

      if (mesh->HasTangentsAndBitangents() && mesh->mTangents && mesh->mBitangents) {
        vertex.tangents = Vector4(
          mesh->mTangents[i].x,
          mesh->mTangents[i].y,
          mesh->mTangents[i].z,
          0.0f);

        vertex.binormals = Vector4(
          mesh->mBitangents[i].x,
          mesh->mBitangents[i].y,
          mesh->mBitangents[i].z,
          0.0f);
      }
      else {
        vertex.tangents = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        vertex.binormals = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
      }

      if (mesh->mTextureCoords[0]) {
        vertex.texture = Vector2(
          mesh->mTextureCoords[0][i].x,
          mesh->mTextureCoords[0][i].y);
      }
      else {
        vertex.texture = Vector2(0.0f, 0.0f);
      }

      m_vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
      const aiFace& face = mesh->mFaces[i];

      for (unsigned int j = 0; j < face.mNumIndices; ++j) {
        uint32_t index = vertexOffset + face.mIndices[j];

        if (index > UINT16_MAX) {
          std::cout << "Error: model has too many vertices for uint16_t indices." << std::endl;
          return false;
        }

        m_indices.push_back(static_cast<uint16_t>(index));
      }
    }
  }

  calculateBoundingBox();
  return true;
}

bool
Model3D::isValid() const {
  return !m_vertices.empty() && !m_indices.empty();
}

uint32
Model3D::getIndexCount() const {
  return static_cast<uint32>(m_indices.size());
}

const
Vector<ModelVertex>& 
Model3D::getVertices() const {
  return m_vertices;
}

bool
Model3D::createBuffers() {
  if (!isValid()) {
    return false;
  }

  GraphicsAPI& grapi = GraphicsAPI::instance();

  m_vertexBuffer = grapi.createVertexBuffer(
    sizeof(ModelVertex) * static_cast<uint32>(m_vertices.size()),
    m_vertices.data());

  m_indexBuffer = grapi.createIndexBuffer(
    sizeof(uint16) * static_cast<uint32>(m_indices.size()),
    m_indices.data());

  return m_vertexBuffer != nullptr && m_indexBuffer != nullptr;
}

SPtr<VertexBuffer> 
Model3D::getVertexBuffer() const {
  return m_vertexBuffer;
}

SPtr<IndexBuffer> 
Model3D::getIndexBuffer() const {
  return m_indexBuffer;
}

void
Model3D::calculateBoundingBox() {
  for (const ModelVertex& vertex : m_vertices) {
    m_boundingBox.growthByPoint({ vertex.position.x,
                                  vertex.position.y,
                                  vertex.position.z});
  }
}

}
