#pragma once
#include "bowUtilitiesRequisites.h"

#if BOW_PLATFORM == BOW_PLATFORM_WINDOWS ||
  BOW_PLATFORM == BOW_PLATFORM_LINUX ||
  BOW_PLATFORM == BOW_PLATFORM_OSX
#include "bowPlatformMath.h"
#endif

namespace bowEngineSDK
{
#if BOW_PLATFORM == BOW_PLATFORM_WINDOWS ||
    BOW_PLATFORM == BOW_PLATFORM_LINUX ||
    BOW_PLATFORM == BOW_PLATFORM_OSX
#include "bowPlatformMath.h"
#endif
  using Math = bowPlatformMath;
#else
#error 
#endif
}