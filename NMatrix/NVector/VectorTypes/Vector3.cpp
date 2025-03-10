/*
 * Vector3.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "Vector3.h"

Vector3::Vector3(double*values) {
	// TODO Auto-generated constructor stub
	new (this) Vector(3,this->entries,false);
	this->copyToValue(values);
}

Vector3::~Vector3() {
}

