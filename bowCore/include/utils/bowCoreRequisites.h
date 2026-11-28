#pragma once 
#include "bowUtilitiesRequisites.h"
#include "bowGraphicsGenerals.h"
#include "bowSTDheaders.h"

#if defined (BOW_CORE_EXPORTS)
  #define BOW_CORE_EXPORT BOW_DLL_EXPORT
#else 
  #define BOW_CORE_EXPORT BOW_DLL_IMPORT
#endif // BOW_CORE_EXPORTS
