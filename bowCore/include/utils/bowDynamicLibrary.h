#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
class DynamicLibrary
{
public:
  BOW_CORE_EXPORT
  DynamicLibrary(const String& _libraryName);

  BOW_CORE_EXPORT
  ~DynamicLibrary() = default;
  
  NODISCARD 
  BOW_CORE_EXPORT
  bool
  load();

  
  template<typename T>
  T
  getSymbol(const String& symbolName);

  BOW_CORE_EXPORT
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
