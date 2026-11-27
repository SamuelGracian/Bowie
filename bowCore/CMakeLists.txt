file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(bowCore SHARED
    ${SOURCES}
    ${HEADERS}
)

SET_ENGINE_DEFAULTS(bowCore)

add_recursive_includes(bowCore)

list (APPEND CMAKE_PREFIX_PATH "D:/DEV/Devlibs/assimp-install")

find_package(assimp CONFIG REQUIRED)

target_link_libraries(bowCore
    PUBLIC bowUtilities
    PUBLIC assimp::assimp
)

target_compile_definitions(bowCore PRIVATE BOW_CORE_EXPORTS=1)

add_custom_command(TARGET bowCore POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:assimp::assimp> $<TARGET_FILE_DIR:bowCore>)