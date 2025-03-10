/*
 * Vector2.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NVECTOR_VECTORTYPES_VECTOR2_H_
#define NMATRIX_NVECTOR_VECTORTYPES_VECTOR2_H_
#include "../NVector.h"
class Vector2 : public Vector {
private:
	double entries[2];
public:
	Vector2(double*values);
	virtual ~Vector2();
};

#endif /* NMATRIX_NVECTOR_VECTORTYPES_VECTOR2_H_ */
