file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(BowieCore SHARED
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(BowieCore PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

SET_ENGINE_DEFAULTS(BowieCore)

target_include_directories(BowieCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(BowieCore
    PUBLIC bowUtilities
)

target_compile_definitions(BowieCore
    PRIVATE BOW_CORE_EXPORTS=1
)