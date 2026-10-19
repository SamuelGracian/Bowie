#pragma once 

/*
* varios namespace o todo dentro de bowEngine
*/
namespace bowEngineSDK
{

namespace GAPI_FORMAT
{
enum K
{
  FORMAT_UNKNOWN = 0,
  FORMAT_D24_UNORM_S8_UINT,
  FORMAT_R8G8B8A8_UNORM,
  FORMAT_R32_FLOAT,
};
}/// namespace GAPI_FORMAT

namespace GAPI_BIND_FLAGS
{
enum K
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
enum K
{
  VERTEX_SHADER = 0,
  PIXEL_SHADER
};
}/// namespace SHADER_TYPE

namespace CULL_MODE
{
enum K
{
  CULL_NONE = 1,
  CULL_FRONT = 2,
  CULL_BACK = 3
};
}/// namespace CULL_MODE

namespace FILL_MODE
{
enum FILL_MODE
{
  FILL_WIREFRAME = 2,
  FILL_SOLID = 3
};
}/// namespace FILL_MODE
}/// namespace bowEngineSDK
