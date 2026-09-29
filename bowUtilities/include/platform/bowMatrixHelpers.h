/*
* @date 25/09/26
*   Helper matrix classes
* 
* Coordinate system begin X = front, Z = Up, Y = Right.
*/

#pragma once

#include "bowMatrix.h"
#include "bowVector3.h"

namespace bowEngineSDK
{
  /********************************************/
  /*  TRANSLATION MATRIX  */
  /********************************************/

class BOW_UTILITIES_EXPORT translationMatrix : public bowMatrix
{
public:

  /*
  * @brief
  *  Constructor for translation matrix given a vector.
  * @param VECTOR3
  */
  translationMatrix(const Vector3& translation)
    : bowMatrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                translation.x, translation.y, translation.z, 1.0f)
  {}

};
}