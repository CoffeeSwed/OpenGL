#include "NVector.h"


/**
 *
 * @param dim dimension
 * @param arr null to create array
 * @param handle_arr true if delete on deconstruct!
 * @note If arr is not null, delete will be called on in it once the instance de-constructs! (if handle_arr is true)
 */

void Vector::reInit(uint dim, double* arr, bool handle_arr, bool delete_old){
	this->rows = dim;
	if(delete_old)
		delete(this->values);

	if(arr == NULL)
		this->values = (double*)std::malloc(sizeof(double)*dim);
	else
		this->values = arr;
	this->tight = !handle_arr;
}

Vector::Vector(uint dim, double* arr, bool handle_arr){
	this->reInit(dim,arr,handle_arr,false);
}

Vector::Vector(){
	this->rows = 0;
	this->values = NULL;
	this->tight = true;
}

Vector::~Vector(){
	if(!this->tight)
		delete(this->values);
}

void Vector::copyToValue(double*arr){
	for(uint i = 0; i < this->rows; i++){
		this->values[i] = arr[i];
	}
}

Vector* NVector::createVectorP(double x, double y, double z){
	return createVectorP((double[]){x,y,z},3);
}

Vector* NVector::createVectorP(double* x,uint dimension){
	Vector* p = (Vector*)std::malloc(sizeof(Vector)+sizeof(double)*(size_t)dimension);
	uint_fast64_t dval = (uint_fast64_t)p;
	dval = dval + (uint_fast64_t)sizeof(Vector);
	new (p) Vector(dimension,(double*)dval,false);
	for(int i = 0; i < dimension; i++){
		p->values[i] = x[i];
	}
	return p;
}

Vector NVector::createVector(double*vals, uint dim){
	Vector p = Vector(dim,NULL,true);
	p.copyToValue(vals);
	return p;
}


void NVector::addVectors(Vector*consumed, Vector* other){
	for(uint i = 0; i < consumed->rows; i++){
		consumed->values[i] += other->values[i];
	}
}

void NVector::subVectors(Vector*consumed, Vector* other){
	for(uint i = 0; i < consumed->rows; i++){
			consumed->values[i] -= other->values[i];
		}
}

double NVector::dotVectors(Vector*left, Vector* other){
	double val = 0;
	for(uint i = 0; i < left->rows; i++){
				val += left->values[i] * other->values[i];
	}
	return val;
}

void NVector::scalarVectors(Vector* consumed, double scalar){
	for(uint i = 0; i < consumed->rows; i++){
			consumed->values[i] *= scalar;
	}
}

void NVector::flatten(float*consumed,Vector * vector){
	for(uint i = 0; i < vector->rows; i++){
		consumed[i] = (float)vector->values[i];
	}
}
