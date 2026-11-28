#pragma once

#include "bowCoreRequisites.h"
#include "bowActor.h"

namespace bowEngineSDK
{
class BOW_CORE_EXPORT SceneGraph
{

private:
  Vector<Actor*> m_children;
};
}
