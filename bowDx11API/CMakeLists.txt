file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_library(bowDx11API SHARED 
						${SOURCES} ${HEADERS}
)

set_target_properties(bowDx11API PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

SET_ENGINE_DEFAULTS(bowDx11API)

target_link_libraries(bowDx11API PUBLIC bowCore d3d11 dxgi d3dcompiler)

add_recursive_includes(bowDx11API)