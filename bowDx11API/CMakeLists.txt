file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_executable(bowDx11API ${SOURCES} ${HEADERS}
)

SET_ENGINE_DEFAULTS(bowDx11API)

target_link_libraries(bowDx11API PUBLIC bowCore)

add_recursive_includes(bowDx11API)