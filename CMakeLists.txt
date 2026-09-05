cmake_minimum_required( VERSION 4.0)

project (Bowie)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS off)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set (PLATFORM_ARCH "x64")
else ()
  set (PLATFORM_ARCH "x86")
endif()

function (set_engine_output_directories target_name )
  set_target_properties (${target_name} PROPERTIES

  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${PLATFORM_ARCH}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${PLATFORM_ARCH}

  #intermediate
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${target_name}/intermediate/${PLATFORM_ARCH}$<CONFIG>
  )
endfunction()

function (set_engine_warning_level target_name)
  if (MSVC)
    target_compile_options(${target_name} PRIVATE /W4 /WX)
  else ()
    target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
  endif ()
endfunction()

function (disable_engine_rtti target_name)
  if (MSVC)
    target_compile_options(${target_name} PRIVATE /GR-)
  else ()
    target_compile_options(${target_name} PRIVATE -fno-rtti)
  endif()
endfunction()

function(set_engine_defaults target_name)
  set_engine_output_directories(${target_name})
  set_engine_warning_level(${target_name})
  disable_engine_rtti(${target_name})
endfunction()

add_subdirectory(bowUtilities)
add_subdirectory(bowUtilitiesTest)