#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class BOW_CORE_EXPORT DynamicLibrary
{
public:
  DynamicLibrary(const String& _libraryName);
  ~DynamicLibrary() = default;

  NODISCARD bool
  load();

  template<typename T>
  T
  getSymbol(const String& symbolName);

  void*
  getSymbol(const String& symbolName);

private:
  void* m_handle = nullptr;
  String m_libraryName;
};

template<typename T>
T
DynamicLibrary::getSymbol(const String& symbolName) {
  if (m_handle == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<T>(getSymbol(symbolName));
}
}/// name space bowEngineSDK
