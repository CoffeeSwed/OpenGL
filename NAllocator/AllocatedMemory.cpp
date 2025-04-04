/*
 * AllocatedMemory.cpp
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#include "AllocatedMemory.h"

std::string AllocatedMemory::toString(){
    std::string part = "";
    part += "size : "+std::to_string(this->size)+"\n";
    part += "size_allocated : "+std::to_string(this->size_allocated);
    for(uint_fast64_t pos = (uint_fast64_t)this+sizeof(AllocatedMemory); pos < (uint_fast64_t)this+this->size_allocated; pos++){
        char* partc = (char*)pos;
        //part += std::to_string((uint_fast8_t)*partc);
        //part += "-";
    }
    return part;
}