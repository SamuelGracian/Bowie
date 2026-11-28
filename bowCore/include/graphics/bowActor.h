#pragma once 

#include "bowCoreRequisites.h"
#include "bowComponent.h"
#include "bowMaterial.h"
#include "bowMatrix.h"
#include "bowModel.h"
#include "bowVector3.h"

namespace bowEngineSDK
{

struct Transform
{
  Vector3 position;
  Vector3 scale;
  Matrix4 rotation;
};

class  Actor
{
 public :

  /**
  * @brief
  *  Default constructor.
  */
  BOW_CORE_EXPORT
  Actor() = default;

  Matrix4
  getTransformMatrix() const;

  Matrix4
  getWorldTransformAsMatrix() const;

  void
  addChild(const SPtr<Actor>& child);

  template <typename T>
  bool 
  hasComponent() const {
    static_assert(std::is_base_of_v<Component, T>);

    if (m_components.empty()) {
      return false;
    }

    for (const auto& Component : m_components) {
      T* componenTypeCast = dynamic_pointer_cast<T>(Component.get());
      if (componenTypeCast == T) {
        return true;
      }
    }

    return false;
  }

 private:
  friend class Actor;
  Vector<UPtr<Component>> m_components;
  Vector<SPtr<Actor>> m_children;
  Actor* m_parent = nullptr; /// nullptr = child of scene graph.
  Transform m_transform;
};
}
