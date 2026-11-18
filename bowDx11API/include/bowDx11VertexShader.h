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
 
  ~Dx11VertexShader();
 
  ID3D11VertexShader* m_shader;
  ID3D11InputLayout* m_InputLayout;
};

Dx11VertexShader::~Dx11VertexShader() {
  safeRelease(m_shader);
  safeRelease(m_InputLayout);
}
}/// name space bowEngineSDK
