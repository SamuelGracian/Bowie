#pragma once 

#include "bowComponent.h"
#include "bowModel.h"

namespace bowEngineSDK
{
class ModelComponent : public Component
{
  FORCEINLINE
  void 
  setModel(const SPtr<Model3D>& _model3D) {
    if (!_model3D->isValid()) {
      BOW_LOG_ERROR("invalid model" << std::endl);
    }
    m_model = _model3D;
  }

  FORCEINLINE
  SPtr<Model3D>
  getModel() const {
    return m_model;
  }

private:
  SPtr<Model3D> m_model;
};
}/// name space bowEngineSDK
