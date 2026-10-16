file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_executable(bowCoreTest ${SOURCES} ${HEADERS}
)

SET_ENGINE_DEFAULTS(bowCoreTest)

target_link_libraries(bowCoreTest PUBLIC bowCore bowUtilities)

target_include_directories(bowCoreTest PUBLIC 
${CMAKE_SOURCE_DIR}/bowUtilities/include
${CMAKE_SOURCE_DIR}/bowCore/include/display
${CMAKE_SOURCE_DIR}/bowCore/include/utils

)