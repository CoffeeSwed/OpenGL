/*
 * Vector5.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NVECTOR_VECTORTYPES_VECTOR5_H_
#define NMATRIX_NVECTOR_VECTORTYPES_VECTOR5_H_
#include "../NVector.h"
class Vector5 : public Vector{
private:
	double entries[5];
public:
	Vector5(double *values);
	virtual ~Vector5();
};

#endif /* NMATRIX_NVECTOR_VECTORTYPES_VECTOR5_H_ */
