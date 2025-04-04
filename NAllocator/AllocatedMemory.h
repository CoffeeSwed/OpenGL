/*
 * AllocatedMemory.h
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#ifndef NALLOCATOR_ALLOCATEDMEMORY_H_
#define NALLOCATOR_ALLOCATEDMEMORY_H_
#include <cstdlib>
#include <cstdint>
#include <string>
class AllocatedMemory {
public:

	uint_fast64_t size_allocated = 0;
	uint_fast64_t size = 0;
	AllocatedMemory* prev = NULL;
	void* owner = NULL;
	std::string toString();

};

#endif /* NALLOCATOR_ALLOCATEDMEMORY_H_ */
