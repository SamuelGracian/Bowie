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

class BOW_UTILITIES_EXPORT TranslationMatrix : public bowMatrix
{
public:

  /*
  * @brief
  *  Constructor for translation matrix given a vector.
  * @param VECTOR3
  */
  TranslationMatrix(const vector3& translation);

};

}