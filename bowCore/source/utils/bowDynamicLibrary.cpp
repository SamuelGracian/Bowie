#include "bowDynamicLibrary.h"

#if defined (BOW_PLATFORM_WIN32)
#include <iostream>
#include "windows.h"
#endif

namespace bowEngineSDK
{
DynamicLibrary::DynamicLibrary(const String& _libraryName)
  : m_libraryName(_libraryName) {}

bool
DynamicLibrary::load() {
#if BOW_PLATFORM_WIN32
  m_handle = static_cast<void*> (LoadLibraryA(m_libraryName.c_str()));
#endif 
  if (m_handle == nullptr) {
#if BOW_PLATFORM_WIN32
    std::cout << "Failed to load library" << std::endl;
    return false;
#endif
  }
  return true;
}

void*
DynamicLibrary::getSymbol(const String& symbolName) {

  if (m_handle == nullptr) {
    std::cout << "The dynamic library is not loaded." << std::endl;
  }

#if defined(BOW_PLATFORM_WIN32)
  void* symbol = reinterpret_cast<void*>(
    GetProcAddress(
      static_cast<HMODULE>(m_handle),
      symbolName.c_str()));
#endif 
  if (symbol == nullptr) {
   std::cout << "Unable to find symbol: " << std::endl;
  }

  return symbol;
}
}
