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
    : width(_width),
      height(_height)
  {}

  /*
  * @brief
  *  Default destructor.
  */
  ~DisplaySurface() = default;

  bool
  init(int32 _width, int32 _height, UNICHAR* windowName);

  void
  processMessages();

  int32
  GetHeight() const { return height; }

  int32
  GetWidth() const { return width; }

  int32
  GetClientWidth()  const { return clientWidth; }

  int32
  GetClientHeight() const { return clientHeight; }

  FORCEINLINE DisplaySurfaceHandler
  GetHandle() const { return handler; }


private:
  int32 width;
  int32 height;

  /*
  * Client sizes
  * *To do* Changed them to be calculated, instead of saved
  */
  int32 clientWidth;
  int32 clientHeight;
  
  /*
  * Window handler
  */
  DisplaySurfaceHandler handler;
};
}//bowEngineSDK
