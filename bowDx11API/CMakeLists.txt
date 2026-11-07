file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_library(bowDx11API SHARED 
						${SOURCES} ${HEADERS}
)

SET_ENGINE_DEFAULTS(bowDx11API)

target_link_libraries(bowDx11API PUBLIC bowCore d3d11 dxgi d3dcompiler dxguid)

add_recursive_includes(bowDx11API)