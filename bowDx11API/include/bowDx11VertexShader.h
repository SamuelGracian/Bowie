#pragma once 

#include "bowVertexShader.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11VertexShader : public VertexShader
{

public:
  Dx11VertexShader() :
   m_shader(nullptr),
   m_InputLayout(nullptr)
  {}
  
  
  ~Dx11VertexShader() = default;
  
  
  ID3D11VertexShader* m_shader;
  ID3D11InputLayout* m_InputLayout;
};
}/// namespace bowEngineSDK
