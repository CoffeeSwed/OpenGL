/*
 * Vector2.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "Vector2.h"

Vector2::Vector2(double*values) {
	// TODO Auto-generated constructor stub
	new (this) Vector(2,this->entries,false);
	this->copyToValue(values);


}

Vector2::~Vector2() {
}



