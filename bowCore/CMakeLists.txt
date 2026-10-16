file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(bowCore SHARED
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(bowCore PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

SET_ENGINE_DEFAULTS(bowCore)

target_include_directories(bowCore PUBLIC
include/display
include/utils
include
bowUtilities/include
)

target_link_libraries(bowCore
    PUBLIC bowUtilities
)

target_compile_definitions(bowCore
    PRIVATE BOW_CORE_EXPORTS=1
)