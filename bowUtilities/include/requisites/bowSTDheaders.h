#pragma once

#include <array>
#include <assert.h>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "bowPlatformTypes.h"

namespace bowEngineSDK
{
  template <typename T, SIZE_T size>
  using Array = std::array<T, size>;
  
  template <typename T>
  using Vector = std::vector<T>;
  
  template <typename T>
  using SPtr = std::shared_ptr<T>;
  
  template <typename T>
  using WeakPtr = std::weak_ptr<T>;
  
  template <typename T>
  using UPtr = std::unique_ptr<T>;
  
  template <typename K, typename V>
  using Map = std::map<K, V>;
  
  template <typename K, typename V>
  using UnorderedMap = std::unordered_map<K, V>;
  
  template <typename T, typename... Args>
  NODISCARD
  SPtr<T> makeShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
  
  template <typename T, typename U>
  NODISCARD
  SPtr<T> staticPointerCast(const SPtr<U>& pointer) noexcept {
    return std::static_pointer_cast<T>(pointer);
  }
  
  using String = std::string;
  using WString = std::wstring;
  using StringStream = std::stringstream;
  
}
