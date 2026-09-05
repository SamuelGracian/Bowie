file (GLOB_RECURSE SOURCES source/*.cpp)
file (GLOB_RECURSE HEADERS include/*.h)

add_library (bowUtilities ${SOURCES} ${HEADERS})

SET_ENGINE_DEFAULTS(bowUtilities)

target_include_directories(bowUtilities PUBLIC
include/math
include/requisites
include/platform)