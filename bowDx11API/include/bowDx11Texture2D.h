#pragma once

#include "bowTexture2D.h"
#include "bowDx11Requisites.h"

namespace bowEngineSDK
{
class Dx11Texture2D : public Texture2D
{
 public:

   /*
   * @brief
   *  Default constructor, sets pointer members as nullptr.
   */
  Dx11Texture2D()
   : texture(nullptr),
    textureView(nullptr)
  {}

  /*
  * @brief
  * Default destructor
  */
  ~Dx11Texture2D() {
    safeRelease(texture);
    safeRelease(textureView);
  }

  /*
  * @brief
  *  Get the witdh of the texture.
  * @param none
  * @return uint32
  */
  FORCEINLINE uint32
  getWidth() const { return m_width; }

  /*
  * @brief
  *  Get the height of the texture.
  * @param none
  * @return uint32
  */
  FORCEINLINE uint32 
  getHeight() const { return m_height; }
  
  /// <summary>
  /// texture member
  /// </summary>
  ID3D11Texture2D* texture;

  /// <summary>
  /// Shader resource view member 
  /// </summary>
  ID3D11ShaderResourceView* textureView;
};
}/// namespace bowEngineSDK
