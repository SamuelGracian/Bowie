#pragma once 

#include "bowPlatformTypes.h"

namespace bowEngineSDK
{

namespace TEXTURE_FORMAT
{
enum E
{
  FORMAT_UNKNOWN = 0,
  D24_UNORM_S8_UINT,
  R32_FLOAT,
  R8G8B8A8_UNORM,
  B8G8R8A8_UNORM,
  R16G16B16A16_FLOAT,
  D32_FLOAT,
  R8_UNORM,
  R8G8_UNORM,
  R16_FLOAT,
  R16G16_FLOAT,
  R32G32B32A32_FLOAT,
  R32_UINT,
};
 using textureFormat = E;
}/// namespace TEXTURE_FORMAT

namespace GRAPHICS_API_BIND_FLAGS //teture bind flags
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
 using gapiBindFlags = E;
}/// namespace GRAPHICS_API_BIND_FLAGS

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


namespace TEXTURE_CREATE_INFO
{
struct E
{
  TEXTURE_TYPE::E type = TEXTURE_TYPE::Texture2D;
  TEXTURE_FORMAT::textureFormat format = TEXTURE_FORMAT::R8G8B8A8_UNORM;
  uint32 width;
  uint32 height;
  uint32 depth;
  uint32 mipLvl;
};
}///namespace TEXTURE_CREATE_INFO

/*
* @brief
*  Depth Stencil View clear flags
*/
namespace ClearFlags
{
enum E : uint8
{
  Depth = 1,
  Stencil = 2
};
}/// namespace DSV_FLAGS
namespace TOPOLOGY_TYPE
{
enum E : uint32
{
  TriangleList = 0,
  TriangleStrip,
  LineList,
  PointList
};
}/// namespate TOPOLOGY_TYPE
}/// namespace bowEngineSDK
