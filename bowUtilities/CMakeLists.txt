file (GLOB_RECURSE SOURCES source/*.cpp)
file (GLOB_RECURSE HEADERS include/*.h)

add_library (bowUtilities SHARED ${SOURCES} ${HEADERS})

set_target_properties(bowUtilities PROPERTIES
	WINDOWS_EXPORT_ALL_SYMBOLS ON
)

SET_ENGINE_DEFAULTS(bowUtilities)

add_recursive_includes(bowUtilities)

target_compile_definitions(bowUtilities PRIVATE BOW_UTILITIES_EXPORTS=1)