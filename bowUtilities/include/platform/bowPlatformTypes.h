#pragma once 
#include <cstdint>
#include <cstddef>

namespace bowEngineSDK
{
  using int8 = std::int8_t;
  using int16 = std::int16_t;
  using int32 = std::int32_t;
  using int64 = std::int64_t;

  using uint8 = std::uint8_t;
  using uin16 = std::uint16_t;
  using uint32 = std::uint32_t;
  using uint64 = std::uint64_t;

  using WCHAR16 = char16_t;
  using UNCHAR = unsigned char;
  using WCHAR32 = char32_t;
  using WCHAR16 = char16_t;
  using UNICHAR = WCHAR16;

  using TYPE_OF_NULL = int32;
  using SIZE_T = std::size_t;
}