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

  int32
  GetHeight() const { return m_height; }

  int32
  GetWidth() const { return m_width; }

  int32
  GetClientWidth()  const { return m_clientWidth; }

  int32
  GetClientHeight() const { return m_clientHeight; }

  FORCEINLINE DisplaySurfaceHandler
  GetHandle() const { return handler; }


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
