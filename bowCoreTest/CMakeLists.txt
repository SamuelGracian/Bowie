file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_executable(bowCoreTest ${SOURCES} ${HEADERS}
)

SET_ENGINE_DEFAULTS(bowCoreTest)

target_link_libraries(bowCoreTest PUBLIC bowCore bowDx11API)
