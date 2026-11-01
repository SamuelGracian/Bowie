#pragma once 

#include "bowPlatformTypes.h"

/*
* varios namespace o todo dentro de bowEngine
*/
namespace bowEngineSDK
{

namespace GAPI_FORMAT //texture format
{
enum E //E
{
  FORMAT_UNKNOWN = 0,
  FORMAT_D24_UNORM_S8_UINT,
  FORMAT_R8G8B8A8_UNKNOWN,
  FORMAT_R32_FLOAT,
};
}/// namespace GAPI_FORMAT

namespace GAPI_BIND_FLAGS //teture bind flags
{
enum E
{
  BIND_VERTEX_BUFFER = (1 << 0),
  BIND_INDEX_BUFFER = (1 << 1),
  BIND_CONSTANT_BUFFER = (1 << 2),
  SHADER_RESOURCE = (1 << 3),
  RENDER_TARGET = (1 << 4),
  DEPTH_STENCIL = (1 << 5)
};
}/// namespace GAPI_BIND_FLAGS

namespace SHADER_TYPE
{
enum E
{
  VERTEX_SHADER = 0,
  PIXEL_SHADER
};
}/// namespace SHADER_TYPE

namespace CULL_MODE
{
enum E
{
  CULL_NONE = 1,
  CULL_FRONT = 2,
  CULL_BACK = 3
};
}/// namespace CULL_MODE

namespace FILL_MODE
{
enum E
{
  FILL_WIREFRAME = 2,
  FILL_SOLID = 3
};
}/// namespace FILL_MODE

static constexpr uint32 BUFFER_HIGHER_AVAILABLE_SLOT = 8;


namespace TEXTURE_TYPE
{
enum E
{
  Texture1D = 0,
  Texture2D,
  Texture3D
};
}/// namespace TEXTURE_TYPE

namespace TEXTURE_FORMAT
{
enum E
{
  Unknown = 0,
  R8G8B8A8_UNORM,
  B8G8R8A8_UNORM,
  B8G8R8A8_SRGB,
  R16G16B16A16_SFLOAT,
  D32_SFLOAT,
  D24_UNORM_S8_UINT,
  R8_UNORM,
  R8G8_UNORM,
  R8G8B8A8_SRGB,
  A2B10G10R10_UNORM,
  B10G11R11_UFLOAT,
  R16_SFLOAT,
  R16G16_SFLOAT,
  R32_SFLOAT,
  R32G32B32A32_SFLOAT,
  R32_UINT,
  D32_SFLOAT_S8_UINT,
};
}/// namespace TEXTURE_FORMAT

}/// namespace bowEngineSDK
