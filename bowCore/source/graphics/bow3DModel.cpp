#include "bow3DModel.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

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

//bool
//Model3D::importModel(const String& fileName,
//                     Vector<uint16>& outIndices,
//                     Vector<SimpleVertex>& outVertex) {

  //Assimp::Importer importer;

  //const aiScene* scene = importer.ReadFile(
  //  fileName,
  //  aiProcess_Triangulate |
  //  aiProcess_FlipUVs |
  //  aiProcess_JoinIdenticalVertices |
  //  aiProcess_CalcTangentSpace);

  //if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
  //  BOW_LOG_ERROR( "Error loading model: " << importer.GetErrorString() << std::endl);
  //  return false;
  //}

  ////for (unsigned int meshIndex = scene->mNumMeshes -1 ; meshIndex != 0; meshIndex--)
  //for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
  //  aiMesh* mesh = scene->mMeshes[meshIndex];
  //  if (!mesh)
  //    continue;

  //  const uint32_t vertexOffset = static_cast<uint32_t>(outVertex.size());

  //  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
  //    SimpleVertex vertex;
  //    vertex.Pos = Vector4(
  //      mesh->mVertices[i].x,
  //      mesh->mVertices[i].y,
  //      mesh->mVertices[i].z,
  //      1.0f);

  //    if (mesh->HasNormals() && mesh->mNormals) {
  //      vertex.Normals = Vector4(
  //        mesh->mNormals[i].x,
  //        mesh->mNormals[i].y,
  //        mesh->mNormals[i].z,
  //        0.0f);
  //    }
  //    else {
  //      vertex.Normals = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
  //    }

  //    if (mesh->HasTangentsAndBitangents() && mesh->mTangents && mesh->mBitangents) {
  //      vertex.Tangent = Vector4(
  //        mesh->mTangents[i].x,
  //        mesh->mTangents[i].y,
  //        mesh->mTangents[i].z,
  //        0.0f);

  //      vertex.Binormal = Vector4(
  //        mesh->mBitangents[i].x,
  //        mesh->mBitangents[i].y,
  //        mesh->mBitangents[i].z,
  //        0.0f);
  //    }
  //    else {
  //      vertex.Tangent = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
  //      vertex.Binormal = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
  //    }

  //    if (mesh->mTextureCoords[0]) {
  //      vertex.Tex = Vector2(
  //        mesh->mTextureCoords[0][i].x,
  //        mesh->mTextureCoords[0][i].y);
  //    }
  //    else {
  //      vertex.Tex = Vector2(0.0f, 0.0f);
  //    }

  //    outVertex.push_back(vertex);
  //  }

  //  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
  //    const aiFace& face = mesh->mFaces[i];

  //    for (unsigned int j = 0; j < face.mNumIndices; ++j) {
  //      uint32_t index = vertexOffset + face.mIndices[j];

  //      if (index > UINT16_MAX) {
  //        std::cout << "Error: model has too many vertices for uint16_t indices." << std::endl;
  //        return false;
  //      }

  //      outIndices.push_back(static_cast<uint16_t>(index));
  //    }
  //  }
  //}

//  return true;
//}
  
}
