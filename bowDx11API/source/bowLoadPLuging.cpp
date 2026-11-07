#include <iostream>

#include "bowDx11Requisites.h"

using namespace bowEngineSDK;

extern "C" BOW_PLUGIN_EXPORT void
loadPluging() { std::cout << "loading dx11 plugiing" << std::endl; }