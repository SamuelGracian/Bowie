file(GLOB_RECURSE SOURCES source/*.cpp
)

file(GLOB_RECURSE HEADERS include/*.h
)

add_executable(bowCoreTest ${SOURCES} ${HEADERS}
)

add_custom_command(TARGET bowCoreTest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/RawData
          $<TARGET_FILE_DIR:bowCoreTest>/RawData
)

SET_ENGINE_DEFAULTS(bowCoreTest)

target_link_libraries(bowCoreTest PRIVATE bowDx11API)
