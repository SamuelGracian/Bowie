file (GLOB_RECURSE SOURCES source/*.cpp)
file (GLOB_RECURSE HEADERS include/*.h)

add_library (bowUtilities SHARED ${SOURCES} ${HEADERS})

set_target_properties(bowUtilities PROPERTIES
	WINDOWS_EXPORT_ALL_SYMBOLS ON
)

SET_ENGINE_DEFAULTS(bowUtilities)

target_include_directories(bowUtilities PUBLIC
include/math
include/requisites
include/platform)