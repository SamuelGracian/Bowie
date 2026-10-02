#pragma once

#include <cstring>
#include <array>
#include <vector>
#include <memory>

#include "bowPlatformtypes.h"

namespace bowEngineSDK
{
template<typename T, SIZE_T size>
using Array = std::array<T, size>;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr;

}
