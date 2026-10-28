#pragma once

#include "bowSamplerState.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11SamplerState : public SamplerState
{
 public:
	Dx11SamplerState() : samplerState(nullptr) {}

	~Dx11SamplerState() {
		if (samplerState) safeRelease(samplerState);
	}

	ID3D11SamplerState* samplerState;
};
}/// namespace bowEngineSDK
