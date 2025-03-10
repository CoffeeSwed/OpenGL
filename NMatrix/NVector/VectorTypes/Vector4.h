/*
 * Vector4.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NVECTOR_VECTORTYPES_VECTOR4_H_
#define NMATRIX_NVECTOR_VECTORTYPES_VECTOR4_H_
#include "../NVector.h"
class Vector4 : public Vector{
private:
	double entries[4];
public:
	Vector4(double*values);
	virtual ~Vector4();
};

#endif /* NMATRIX_NVECTOR_VECTORTYPES_VECTOR4_H_ */
