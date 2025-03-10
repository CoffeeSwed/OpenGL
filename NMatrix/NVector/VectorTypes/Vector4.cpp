/*
 * Vector4.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "Vector4.h"

Vector4::Vector4(double*values) {
	// TODO Auto-generated constructor stub
	new (this) Vector(4,this->entries,false);
	this->copyToValue(values);

}

Vector4::~Vector4() {
}

