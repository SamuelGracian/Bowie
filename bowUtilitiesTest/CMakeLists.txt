file (GLOB_RECURSE SOURCES source/*.cpp)
file (GLOB_RECURSE HEADERS include/*.h)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.16.0
)

FetchContent_MakeAvailable(Catch2)

add_executable (bowUtilitiesTest ${SOURCES} ${HEADERS})

SET_ENGINE_DEFAULTS(bowUtilitiesTest)

target_link_libraries(bowUtilitiesTest PRIVATE bowUtilities Catch2::Catch2WithMain)

target_include_directories(bowUtilitiesTest PUBLIC bowUtilities/include)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include (CTest)
include (Catch)
catch_discover_tests (bowUtilitiesTest)