#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "bowModule.h"

namespace bowEngineSDK
{

// regular module use
class  ModuleTest : public Module<ModuleTest>
{
public:
  ModuleTest() = default;
  virtual ~ModuleTest() = default;

  int32 getValue() const {
    static int32 _value = 42;
    return _value;
  }
};

// Fake graphics api
class SubModuleTestBase : public Module<SubModuleTestBase>
{
public:
  SubModuleTestBase() = default;
  virtual ~SubModuleTestBase() = default;

  virtual int32 getValue() const {
    static int32 _value = 1;
    return _value;
  }
};

// Fake graphics api implementation (DX11, DX12, Vulkan, OpenGL, etc)
class SubModuleTest : public SubModuleTestBase
{
public:
  SubModuleTest() = default;
  virtual ~SubModuleTest() = default;

  int32 getValue() const override {
    static int32 _value = 24;
    return _value;
  }
};

TEST_CASE("Module operations", " [Module]") {
  
  SECTION("Start up and shut down") {
    REQUIRE(ModuleTest::isStarted() == false);
    REQUIRE(ModuleTest::instancePtr() == nullptr);

    ModuleTest::startUp();
    REQUIRE(ModuleTest::isStarted() == true);
    REQUIRE(ModuleTest::instancePtr() != nullptr);
    REQUIRE(ModuleTest::instance().getValue() == 42);

    ModuleTest::shutDown();
    REQUIRE(ModuleTest::isStarted() == false);
  }

  SECTION("Start up with sub type") {
    REQUIRE(SubModuleTestBase::isStarted() == false);
    REQUIRE(SubModuleTestBase::instancePtr() == nullptr);

    // GraphicsAPI::startUp<DirectX11>();
    SubModuleTestBase::startUp<SubModuleTest>();
    REQUIRE(SubModuleTestBase::isStarted() == true);
    REQUIRE(SubModuleTestBase::instancePtr() != nullptr);
    REQUIRE(SubModuleTestBase::instance().getValue() == 24);
    REQUIRE(SubModuleTestBase::instance().getValue() != 1);

    SubModuleTestBase::shutDown();
    REQUIRE(SubModuleTestBase::isStarted() == false);
  }
}



}