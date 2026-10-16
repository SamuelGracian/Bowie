/************************************************************************/
/**
 * @file bowWindow.h
 * @author Samuel G
 * @date 13/10/2026
 * @brief
 *
 */
/*************************************************************************/

#pragma once

#include "bowCoreRequisites.h"

namespace bowEngineSDK
{
using DisplaySurfaceHandler = void*;

class DisplaySurface
{
public:

  /*
  * @brief
  *  Default constructor.
  */
  DisplaySurface() = default;

  /*
  * @brief
  * Constructor from given values
  */
  DisplaySurface(int32 _width, int32 _height)
    : m_width(_width),
      m_height(_height)
  {}

  /*
  * @brief
  *  Default destructor.
  */
  ~DisplaySurface() ;

  bool
  init(int32 _width, int32 _height, const String& windowName);

  void
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
  getHandle() const { return handler; }


private:
  int32 m_width;
  int32 m_height;

  /*
  * Client sizes
  * *To do* Changed them to be calculated, instead of saved
  */
  int32 m_clientWidth;
  int32 m_clientHeight;
  
  /*
  * Window handler
  */
  DisplaySurfaceHandler handler;
};
}//bowEngineSDK
