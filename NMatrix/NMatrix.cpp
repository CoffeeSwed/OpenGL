/*
 * NMatrix.cpp
 *
 *  Created on: Mar 10, 2025
 *      Author: norman
 */

#include "NMatrix.h"

NAllocator* NMatrix::getAllocator(){
	static NAllocator allocator = NAllocator();
	return (NAllocator*)&allocator;
}

void NMatrix::init(uint rows, uint columns, double*to_copy, bool already_init){
	this->rows = rows;
	this->columns = columns;
	if(!already_init){
		this->values = (double*)NMatrix::getAllocator()->allocate(sizeof(double)*(size_t)rows*(size_t)columns);
		if(to_copy != NULL){
			std::memcpy((void*)this->values,to_copy,sizeof(double)*(size_t)rows*(size_t)columns);
		}
	}else{
		this->values = to_copy;
	}

}

NMatrix::NMatrix(uint rows, uint columns, double*to_copy) {
	// TODO Auto-generated constructor stub
	this->init(rows,columns,to_copy);
}

NMatrix::~NMatrix() {
	// TODO Auto-generated destructor stub
	if(this->values != NULL)
		NMatrix::getAllocator()->unallocate(this->values);
	this->values = NULL;
}
//copy constructor
NMatrix::NMatrix(const NMatrix &other) {
	// TODO Auto-generated constructor stub

	this->init(other.rows,other.columns,other.values);
}

// Move constructor
NMatrix::NMatrix(NMatrix &&other) {
	// TODO Auto-generated constructor stub
	this->init(other.rows,other.columns,other.values,true);
	other.values = NULL;
}


//Copy assignment operator
NMatrix& NMatrix::operator=(const NMatrix &other) {
	// TODO Auto-generated method stub
	if(this != &other){
		NMatrix::getAllocator()->unallocate(this->values);
		this->init(other.rows,other.columns,other.values);
	}
	return *this;
}

// Move assignment operator
NMatrix& NMatrix::operator=(NMatrix &&other) {
	// TODO Auto-generated method stub
	if(this != &other){
		NMatrix::getAllocator()->unallocate(this->values);
		this->init(other.rows,other.columns,other.values,true);
		other.values = NULL;

	}
	return *this;
}


NMatrix::EqualReturnRes NMatrix::isSameMatrix(NMatrix* other){
	if(this->values == NULL || other->values == NULL)
		return EqualReturnRes::POINTS_TO_NULL;
	if(this->values == other->values)
		return EqualReturnRes::POINTS_TO_SAME;
	if(this->columns == other->columns && this->rows == other->rows){
		for(uint index = 0; index < this->rows*this->columns; index++){
			if(this->values[index] != other->values[index])
				return EqualReturnRes::VALUES_DONT_MATCH;
		}
		return EqualReturnRes::REPRESENT_SAME;
	}
	return EqualReturnRes::DIMENSION_DONT_MATCH;
}

std::string NMatrix::toString(){
	std::string res = "{";
	return res+"}";
}

NMatrix NMatrix::getTranspose(){
	NMatrix res = NMatrix(this->columns,this->rows);
	for(uint index = 0; index < this->columns*this->rows;index++){
		uint row = this->getRow(index);
		uint column = this->getColumn(index);
		res.values[res.getIndex(column,row)] = this->values[index];
	}
	return res;
}

uint NMatrix::getIndex(uint row, uint column){
	return (row*this->columns + column);
}

uint NMatrix::getRow(uint index){
	return index/this->columns;
}

uint NMatrix::getColumn(uint index){
	return index % this->columns;
}

uint NMatrix::getElements(){
	return this->columns*this->rows;
}

NMatrix NMatrix::getMinor(uint row, uint column){
	NMatrix res = NMatrix(this->rows-1,this->columns-1);

	return res;
}
