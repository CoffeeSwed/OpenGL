/*
 * NMatrix.h
 *
 *  Created on: Mar 10, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NMATRIX_H_
#define NMATRIX_NMATRIX_H_
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "../NAllocator/NAllocator.h"
class NMatrix {
private:
	static NAllocator* getAllocator();
	uint rows, columns;
	void init(uint rows, uint columns, double*to_copy=NULL, bool already_init = false);
public:
	double* values;

	enum EqualReturnRes{DIMENSION_DONT_MATCH = 0, VALUES_DONT_MATCH = -1, POINTS_TO_NULL = -2, POINTS_TO_SAME = 2, REPRESENT_SAME = 1};

	NMatrix(uint rows, uint columns, double*to_copy=NULL);
	virtual ~NMatrix();
	NMatrix(const NMatrix &other);
	NMatrix(NMatrix &&other);
	NMatrix& operator=(const NMatrix &other);
	NMatrix& operator=(NMatrix &&other);
	EqualReturnRes isSameMatrix(NMatrix *other);
	std::string toString();

	NMatrix getTranspose();
	uint getIndex(uint row, uint column);
	uint getRow(uint index);
	uint getColumn(uint index);
	NMatrix getMinor(uint row, uint column);
	double getDeterminant();
	uint getElements();
};

#endif /* NMATRIX_NMATRIX_H_ */
