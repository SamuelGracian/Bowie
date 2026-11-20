/************************************************************************/
/**
 * @file bowWindow.h
 * @author Samuel G
 * @date 13/10/2026
 * @brief
 *  Base class to represent a window.
 */
/*************************************************************************/

#pragma once

#if BOW_PLATFORM ==  BOW_PLATFORM_WIN32
#include <Windows.h>
#endif

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
using DisplaySurfaceHandler = void*;

class BOW_CORE_EXPORT DisplaySurface
{
 public:

  /*
  * @brief
  *  Default constructor.
  */
  DisplaySurface() = default;

  DisplaySurface(const DisplaySurface&) = delete;

  DisplaySurface
  operator=(const DisplaySurface&) = delete;

  /*
  * @brief
  * Constructor from given values
  */
  DisplaySurface(int32 _width, int32 _height)
    : m_width(_width),
      m_height(_height),
      m_handler(nullptr)
  {}

  /*
  * @brief
  *  Default destructor.
  */
  ~DisplaySurface() ;

  bool
  init(int32 _width, int32 _height, const String& windowName);

  bool
  processMessages();

  FORCEINLINE int32
  getHeight() const { return m_height; }

  FORCEINLINE int32
  getWidth() const { return m_width; }

  FORCEINLINE int32
  getClientWidth()  const { return m_clientWidth; }

  FORCEINLINE int32
  getClientHeight() const { return m_clientHeight; }

  FORCEINLINE DisplaySurfaceHandler
  getHandle() const { return m_handler; }

private:
  int32 m_width = 0;
  int32 m_height = 0;

  /*
  * Client sizes
  * *To do* Changed them to be calculated, instead of saved
  */
  int32 m_clientWidth = 0;
  int32 m_clientHeight = 0;
  
  /*
  * Window handler
  */
  DisplaySurfaceHandler m_handler = nullptr;
};
}/// name space bowEngineSDK
