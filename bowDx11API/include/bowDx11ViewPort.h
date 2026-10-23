#pragma once
#include "bowViewPort.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11ViewPort :public ViewPort
{
	Dx11ViewPort() :
		m_viewPort(nullptr) {}

	~Dx11ViewPort() = default;

	D3D11_VIEWPORT* m_viewPort;
};


}/// namespace BowEngineSDK
