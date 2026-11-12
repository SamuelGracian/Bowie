#include <iostream>

#include "bowDx11Requisites.h"
#include "bowDx11GraphicsAPI.h"

using namespace bowEngineSDK;

BOW_PUGLIN_EXPORT_EXTERN void
loadPluging() { GraphicsAPI::startUp<Dx11GraphicsAPI>(); }