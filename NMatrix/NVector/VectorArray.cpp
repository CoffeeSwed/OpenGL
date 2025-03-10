/*
 * VectorArray.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "VectorArray.h"

VectorArray::VectorArray(uint rows, uint columns, double*values){

	this->sizepervector = sizeof(Vector)+sizeof(double)*rows;
	this->vectors = (Vector*)std::malloc(sizepervector*(size_t)columns);
	initVectorArray(this,this->vectors,rows,columns,values);
	this->is_tight = false;
}

VectorArray::~VectorArray(){
	if(!this->is_tight)
		delete(this->vectors);

}

void VectorArray::initVectorArray(VectorArray* vecarr, Vector* arraystart, uint dimension, uint size,double*values){
	size_t size_per_vector = sizeof(Vector) + sizeof(double)*dimension;
	uint_fast64_t pos = (uint_fast64_t)vecarr;
	VectorArray* arr = (VectorArray*)pos;
	arr->sizepervector = size_per_vector;
	arr->columns = size;
	arr->vectors = (Vector*)arraystart;
	pos = (uint_fast64_t)arr->vectors;

	for(uint i = 0; i < size; i++){


		Vector* p = arr->getVec(i);
		pos = (uint_fast64_t)p;
		new (p) Vector(dimension,(double*)(pos+sizeof(Vector)),false);
		if(values != NULL){
			for(uint row = 0; row < dimension; row++){
				uint index = row*size+i;
				p->values[row] = values[index];
			}
		}

	}
	arr->rows = dimension;

}


VectorArray* VectorArray::createTightVectorArray(uint dimension, uint size, double*values){
	size_t size_per_vector = sizeof(Vector) + sizeof(double)*dimension;
	size_t size_structarray = sizeof(VectorArray)+size_per_vector*(size_t)size;
	uint_fast64_t pos = (uint_fast64_t)std::malloc(size_structarray);
	VectorArray* arr = (VectorArray*)pos;
	arr->sizepervector = size_per_vector;
	arr->columns = size;
	pos = pos+(uint_fast64_t)sizeof(VectorArray);
	arr->vectors = (Vector*)pos;
	initVectorArray(arr,arr->vectors,dimension,size,values);
	arr->is_tight = true;


	return arr;
}

bool VectorArray::isEqual(VectorArray* other){
	if(this->columns == other->columns && this->rows == other->rows){
		for(uint column = 0; column < this->columns; column++){
			for(uint row = 0; row < this->rows; row++){
				if(this->getVec(column)->values[row] != other->getVec(column)->values[row])
					return false;
			}
		}
		return true;
	}
	return false;
}

Vector* VectorArray::getVec(uint column){
	uint_fast64_t pos = (uint_fast64_t)this->vectors;
	pos = pos + (uint_fast64_t)this->sizepervector*column;
	return (Vector*)pos;
}

VectorArray VectorArray::getTranspose(){
	VectorArray sacrifice = VectorArray(this->columns,this->rows,NULL);
	for(int column = 0; column < this->columns; column++){
		Vector* vec = this->getVec(column);
		for(int row = 0; row < this->rows; row++){
			sacrifice.getVec(row)->values[column] = vec->values[row];
		}
	}
	return sacrifice;

}

VectorArray VectorArray::getAdjoint(){
	VectorArray p = VectorArray(this->rows,this->columns,NULL);
	for(uint row = 0; row < this->rows; row++){
		for(uint column = 0; column < this->columns; column++){
			p.getVec(column)->values[row] = this->getCoFactor(row,column);
		}
	}
	return p;
}

double VectorArray::getCoFactor(uint row, uint column){
	double val = ((row+column) % 2 == 0) ? 1 : -1;
	val = val * this->eliminateRowAndColumn(row,column).getDeterminent();
	return val;
}

double VectorArray::getDeterminent(){
	if(this->columns == 1)
		return this->vectors->values[0];
	if(this->columns == 2)
	{
		Vector* first = this->getVec(0);
		Vector* second = this->getVec(1);
		return first->values[0]*second->values[1] - second->values[0]*first->values[1];
	}
	double sum = 0.0;
	for(int j = 0; j < this->columns; j++){
		sum += this->getVec(j)->values[0]*this->getCoFactor(0,j);
	}
	return sum;
}

VectorArray VectorArray::eliminateRowAndColumn(uint row, uint column){
	VectorArray res = VectorArray(this->rows-1, this->columns-1,NULL);
	uint irow = 0;
	uint icolumn = 0;
	for(uint ucolumn = 0; ucolumn < this->columns; ucolumn++){
		if(ucolumn == column)
			continue;
		Vector* vec = res.getVec(icolumn);
		Vector* oth = this->getVec(ucolumn);
		for(uint urow = 0; urow < this->rows; urow++){
			if(urow == row)
				continue;

			vec->values[irow] = oth->values[urow];

			irow = (irow + 1) % res.rows;
			if(irow == 0)
				icolumn++;
		}
	}
	return res;
}

std::string VectorArray::to_string(){
	std::string res = "{";
	for(uint row = 0; row < this->rows; row++){
		for(uint column = 0; column < this->columns; column++){
			res += std::to_string(this->getVec(column)->values[row]);
			if(column + 1 != this->columns)
				res += ", ";
		}

		if(row + 1 != this->rows)
			res += "\n";
	}
	return res+"}";
}

void VectorArray::swap(VectorArray& other){
	std::swap(this->columns,other.columns);
	std::swap(this->is_tight,other.is_tight);
	std::swap(this->vectors,other.vectors);
	std::swap(this->rows,other.rows);
	std::swap(this->sizepervector,other.sizepervector);

}
