#pragma once 

#include "bowPlatformTypes.h"

namespace bowEngineSDK
{

namespace TEXTURE_FORMAT
{
enum E
{
  kFORMAT_UNKNOWN = 0,
  kD24_UNORM_S8_UINT,
  kR32_FLOAT,
  kR8G8B8A8_UNORM,
  kB8G8R8A8_UNORM,
  kR16G16B16A16_FLOAT,
  kD32_FLOAT,
  kR8_UNORM,
  kR8G8_UNORM,
  kR16_FLOAT,
  kR16G16_FLOAT,
  kR32G32B32A32_FLOAT,
  kR32_UINT,
  kR16_UINT
};
}/// name space TEXTURE_FORMAT

namespace GRAPHICS_API_BIND_FLAGS //texture bind flags
{
enum E
{
  kBIND_VERTEX_BUFFER = (1 << 0),
  kBIND_INDEX_BUFFER = (1 << 1),
  kBIND_CONSTANT_BUFFER = (1 << 2),
  kSHADER_RESOURCE = (1 << 3),
  kRENDER_TARGET = (1 << 4),
  kDEPTH_STENCIL = (1 << 5)
};
}/// name space GRAPHICS_API_BIND_FLAGS

namespace SHADER_TYPE
{
enum E
{
  kVERTEX_SHADER = 0,
  kPIXEL_SHADER
};
}/// name space SHADER_TYPE

namespace CULL_MODE
{
enum E
{
  kCULL_NONE = 1,
  kCULL_FRONT = 2,
  kCULL_BACK = 3
};
}/// name space CULL_MODE

namespace FILL_MODE
{
enum E
{
  kFILL_WIREFRAME = 2,
  kFILL_SOLID = 3
};
}/// name space FILL_MODE

static constexpr uint32 BUFFER_HIGHER_AVAILABLE_SLOT = 8;


namespace TEXTURE_TYPE
{
enum E
{
  kTexture1D = 0,
  kTexture2D,
  kTexture3D
};
}/// name space TEXTURE_TYPE


struct TEXTURE_CREATE_INFO
{
  TEXTURE_TYPE::E type = TEXTURE_TYPE::kTexture2D;
  TEXTURE_FORMAT::E format = TEXTURE_FORMAT::kR8G8B8A8_UNORM;
  uint32 width = 0;
  uint32 height = 0;
  uint32 depth = 0;
  uint32 mipLvl = 0;
};///struct TEXTURE_CREATE_INFO


/*
* @brief
*  Depth Stencil View clear flags
*/
namespace CLEAR_FLAGS
{
enum E : uint8
{
  kDepth = 1,
  kStencil = 2
};
}/// name space DSV_FLAGS
namespace TOPOLOGY_TYPE
{
enum E : uint32
{
  kNone = 0,
  kTriangleList,
  kTriangleStrip,
  kLineList,
  kPointList
};
}/// name space TOPOLOGY_TYPE

namespace SHADER_STAGE
{
enum E : uint32
{
  kVertex = 1 << 0,
  kPixel = 1 << 1,
  kAll = kVertex | kPixel
};
}/// name space SHADER_STAGE

}/// name space bowEngineSDK
