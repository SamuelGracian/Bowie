/*
* @date 25/09/26
*   Helper matrix classes
* 
* Coordinate system begin X = front, Z = Up, Y = Right.
*/

#pragma once

#include "bowMatrix.h"
#include "bowVector3.h"

namespace bowEngineSDK{
  /********************************************/
  /*  TRANSLATION MATRIX  */
  /********************************************/

class TranslationMatrix : public Matrix4
{
public:

  /*
  * @brief
  *  Constructor for translation matrix given a vector.
  *  
  *   This constructor puts the translation in the last row.
  * @param VECTOR3
  */
  explicit TranslationMatrix(const Vector3& translation)
    : Matrix4(1.0f, 0.0f, 0.0f,0.0f,
              0.0f, 1.0f,0.0f, 0.0f,
              0.0f,0.0f, 1.0f, 0.0f,
            translation.x, translation.y, translation.z, 1.0f)
  {}

};
}
