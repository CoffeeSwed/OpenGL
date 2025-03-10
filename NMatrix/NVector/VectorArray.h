/*
 * VectorArray.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 *      typedef struct _VectorArray{
	uint amount;
	size_t sizepervector;
	Vector* vectors;

} VectorArray;
 */

#ifndef NMATRIX_NVECTOR_VECTORARRAY_H_
#define NMATRIX_NVECTOR_VECTORARRAY_H_
#include "NVector.h"
#include <exception>

class VectorArray {
public:
	bool is_tight;
	uint columns;
	uint rows;
	size_t sizepervector;
	Vector* vectors = NULL;
	VectorArray(uint rows, uint columns, double*values = NULL);
	~VectorArray();

	bool isEqual(VectorArray* other);
	static VectorArray* createTightVectorArray(uint dimension, uint size, double* values = NULL);
	Vector* getVec(uint column);
	VectorArray getTranspose();
	double getCoFactor(uint row, uint column);
	VectorArray getAdjoint();
	double getDeterminent();
	VectorArray eliminateRowAndColumn( uint row, uint column);
	std::string to_string();

	VectorArray& operator=(VectorArray other)
	{
		other.swap(*this);
		return *this;
	}

private:
	static void initVectorArray(VectorArray* vecarr, Vector* arraystart, uint dimension, uint size, double*values);
	void swap(VectorArray& other);
};

#endif /* NMATRIX_NVECTOR_VECTORARRAY_H_ */
