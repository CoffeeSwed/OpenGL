/*
 * Vector5.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "Vector5.h"

Vector5::Vector5(double *values) {
	// TODO Auto-generated constructor stub
	new (this) Vector(5,this->entries,false);
	this->copyToValue(values);
}


Vector5::~Vector5() {
}
