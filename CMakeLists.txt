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
  bow_set_debug_definitions(${target_name})
endfunction()

function(add_recursive_includes target)
  file(GLOB_RECURSE _hdrs CONFIGURE_DEPENDS
       ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
  set(_dirs "")
  foreach(h ${_hdrs})
      get_filename_component(d ${h} DIRECTORY)
      list(APPEND _dirs ${d})
  endforeach()
  list(REMOVE_DUPLICATES _dirs)
  target_include_directories(${target} PUBLIC ${_dirs})
endfunction()

function (bow_set_debug_definitions target)
  target_compile_definitions(${target} PUBLIC
        $<$<CONFIG:Debug>:BOW_DEBUG_MODE=1>
        $<$<NOT:$<CONFIG:Debug>>:BOW_DEBUG_MODE=0>)
endfunction()

add_subdirectory(bowUtilities)
add_subdirectory(bowUtilitiesTest)
add_subdirectory(bowCore)
add_subdirectory(bowCoreTest)
add_subdirectory(bowDx11API)
