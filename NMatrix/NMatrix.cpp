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
		this->values = (double*)NMatrix::getAllocator()->allocate(sizeof(double)*this->getElements());
		if(to_copy != NULL){
			std::memcpy((void*)this->values,to_copy,sizeof(double)*this->getElements());
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
	//std::cout << "MOVE ASSIGN!\n";
	//std::cout << this->toString() << " -> " << other.toString() << "\n";
	if(this != &other){
		
		
		NMatrix::getAllocator()->unallocate(this->values);
		this->init(other.rows,other.columns,other.values,true);
		other.values = NULL;

	}
	return *this;
}


NMatrix::EqualReturnRes NMatrix::isSameMatrix(NMatrix* other, double margins){
	if(this->values == NULL || other->values == NULL)
		return EqualReturnRes::POINTS_TO_NULL;
	if(this->values == other->values)
		return EqualReturnRes::POINTS_TO_SAME;
	if(this->columns == other->columns && this->rows == other->rows){
		for(uint index = 0; index < this->rows*this->columns; index++){
			if(this->values[index] != other->values[index] && margins == 0)
				return EqualReturnRes::VALUES_DONT_MATCH;
			if(margins != 0){
				double difference = this->values[index] - other->values[index];
				difference = difference < 0 ? -difference : difference;
				if(difference > margins){
					return EqualReturnRes::VALUES_DONT_MATCH;
				}
			}
		}
		return EqualReturnRes::REPRESENT_SAME;
	}
	return EqualReturnRes::DIMENSION_DONT_MATCH;
}

std::string NMatrix::toString(){
	std::string res = "{";
	for(uint row = 0; row < this->rows; row++){
		for(uint column = 0; column < this->columns; column++){
			if(column != 0)
				res+= ", ";
			if(column == 0 && row != 0)
				res+= "\n";
			res += std::to_string(this->values[this->getIndex(row,column)]);
		}
	}
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

uint NMatrix::getRows(){
	return this->rows;
}

uint NMatrix::getColumns(){
	return this->columns;
}

void NMatrix::applyScalar(double num){
	for(uint index = 0; index < this->getElements(); index++){
		this->values[index] = num*this->values[index];
	}
}

NMatrix NMatrix::getMinor(uint row, uint column){
	NMatrix res = NMatrix(this->rows-1,this->columns-1);
	uint index = 0;
	for(uint i = 0; i < this->getElements(); i++){
		if(this->getColumn(i) != column && this->getRow(i) != row){
			res.values[index] = this->values[i];
			index++;
		}
	}
	return res;
}

double NMatrix::getCoFactor(uint row, uint column){
	double part = ((row+column) % 2 == 0) ? 1 : -1;
	return part*this->getMinor(row,column).getDeterminant();
}

double NMatrix::getDeterminant(){
	if(this->columns == 1){
		return this->values[0];
	}
	if(this->columns == 2){
		return (double)(this->values[0]*this->values[3] - this->values[1]*this->values[2]);
	}
	double sum = 0.0;
	for(uint j = 0; j < this->columns; j++){
		sum = sum + this->values[j]*this->getCoFactor(0,j);
	}
	return sum;
}

NMatrix NMatrix::multiply(NMatrix other){
	NMatrix resulting = NMatrix(this->columns,other.columns);
	for(uint row = 0; row < this->columns; row++){
		for(uint column = 0; column < other.columns;column++){
			double resdot = 0;
			for(uint i = 0; i < this->columns; i++){
				resdot += this->values[this->getIndex(row,i)]*other.values[other.getIndex(i,column)];
			}
			resulting.values[resulting.getIndex(row,column)] = resdot;
		}
	}
	return resulting;
}

NMatrix NMatrix::terminateColumn(uint killing_column){
	NMatrix res = NMatrix(this->rows, this->columns-1);
	for(uint row = 0; row < this->rows; row++){
		for(uint column = 0; column < this->columns; column++){
			if(column == killing_column)
				continue;
			res.values[res.getIndex(row,column - (column > killing_column ? 1 : 0))] = this->values[this->getIndex(row,column)];
		}
	}

	return res;
}

NMatrix NMatrix::terminateRow(uint killing_row){
	NMatrix res = NMatrix(this->rows - 1, this->columns);
	for(uint row = 0; row < this->rows; row++){
		if(row == killing_row)
			continue;
		for(uint column = 0; column < this->columns; column++){
			res.values[res.getIndex(row - (row > killing_row ? 1 : 0),column)] = this->values[this->getIndex(row,column)];

		}
	}
	return res;
}

NMatrix NMatrix::appendRow(double* values){
	NMatrix res = NMatrix(this->rows+1,this->columns);
	for(uint index = 0; index < this->getElements(); index++){
		res.values[index] = this->values[index];
	}
	uint p = 0;
	for(uint index = this->getElements(); index < res.getElements(); index++){
		res.values[index] = values[p];
		p++;
	}
	return res;
}

NMatrix NMatrix::getAdjoint(){
	NMatrix matrix = NMatrix(this->rows,this->columns);
	for(uint row = 0; row < this->rows; row++){
		for(uint column = 0; column < this->columns; column++){
			matrix.values[matrix.getIndex(row,column)] = this->getCoFactor(row,column);
		}
	}
	return matrix.getTranspose();
}

NMatrix NMatrix::getInverse(){
	NMatrix inv = NMatrix(this->rows,this->columns);
	if(this->rows == 2){
		NMatrix res = NMatrix(2,2,(double[]){
			this->values[3], -this->values[1],
			-this->values[2], this->values[0]
		});
		res.applyScalar(1.0/(this->values[0]*this->values[3] - this->values[1]*this->values[2]));
		return res;
	}else{
		for(uint row = 0; row < this->rows; row++){
			for(uint column = 0; column < this->columns; column++){
				inv.values[this->getIndex(row,column)] = this->getCoFactor(row,column);

			}
		}
		double det = this->getDeterminant();
		inv = inv.getTranspose();
		inv.applyScalar((double)1.0/det);
	}
	return inv;
}

NMatrix NMatrix::createTranslation3D(double r, double s, double t){
	NMatrix res = NMatrix(4,4,(double[]){
		1,0,0,r,
		0,1,0,s,
		0,0,1,t,
		0,0,0,1
	});
	

	return res;
}

NMatrix NMatrix::createTranslation2D(double r, double s){
	NMatrix res = NMatrix(3,3,(double[]){
		1,0,r,
		0,1,s,
		0,0,1
	});
	return res;
}

NMatrix NMatrix::createRotation2D(double r){
	NMatrix res = NMatrix(2,2);
	res.values[0] = cos(r);
	res.values[1] = -sin(r);
	res.values[2] = sin(r);
	res.values[3] = cos(r);
	return res;
}

NMatrix NMatrix::createRotation3DX(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		1, 0, 0,
		0, cos(r), -sin(r),
		0, sin(r), cos(r)
	});return res;
}

NMatrix NMatrix::createRotation3DY(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		cos(r), 0, sin(r),
		0, 1, 0,
		-sin(r), 0, cos(r)
	});return res;
}

NMatrix NMatrix::createRotation3DZ(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		cos(r), -sin(r), 0,
		sin(r), cos(r), 0,
		0, 0, 1
	});return res;
}