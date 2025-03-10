/*
 * Vector3.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NVECTOR_VECTORTYPES_VECTOR3_H_
#define NMATRIX_NVECTOR_VECTORTYPES_VECTOR3_H_
#include "../NVector.h"
class Vector3 : public Vector {
private:
	double entries[3];
public:
	Vector3(double*values);
	virtual ~Vector3();
};

#endif /* NMATRIX_NVECTOR_VECTORTYPES_VECTOR3_H_ */
