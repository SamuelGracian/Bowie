
#include "bowActor.h"

namespace bowEngineSDK
{
Matrix4
Actor::getTransformMatrix() const {
  return Matrix4::IDENTITY *
    Matrix4::fromScaleVector(m_transform.scale) *
    //Matrix4::fromRotationMatrix(m_transform.rotation) *
    Matrix4::fromTranslationVector(m_transform.position);
}

Matrix4
Actor::getWorldTransformAsMatrix() const {
  Matrix4 matrixReturn = getTransformMatrix();
  if (m_parent) {
    matrixReturn *= m_parent->getWorldTransformAsMatrix();
  }
  return matrixReturn;
}
void 
Actor::addChild(const SPtr<Actor>& child) {
  m_children.push_back(child);
  child->m_parent = this;
}


}/// name space bowEngineSDK
