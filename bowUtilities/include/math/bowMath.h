#pragma once
#include "bowUtilitiesRequisites.h"

#if BOW_PLATFORM == BOW_PLATFORM_WIN32 || \
  BOW_PLATFORM == BOW_PLATFORM_LINUX   || \
  BOW_PLATFORM == BOW_PLATFORM_OSX
#include "bowPlatformMath.h"
#include "bowPlatformVector2.h"
#endif

namespace bowEngineSDK
{
#if BOW_PLATFORM == BOW_PLATFORM_WIN32 || \
    BOW_PLATFORM == BOW_PLATFORM_LINUX || \
    BOW_PLATFORM == BOW_PLATFORM_OSX
using Math = PlatformMath;
using Vector2 = Vector2;
#else

#pragma error "No known platform"

#endif
}