#include <catch2/catch_test_macros.hpp>

#include"bowMath.h"

using namespace bowEngineSDK;

TEST_CASE("Math::Trigonometry", "[Math]") {
  SECTION("Cos") {
    REQUIRE(Math::cos(0.0f) == 1.0f);
  }

}