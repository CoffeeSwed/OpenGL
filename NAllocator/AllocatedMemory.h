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
class AllocatedMemory {
public:

	size_t size_allocated = 0;
	size_t size = 0;
	AllocatedMemory* prev = NULL;
	void* owner = NULL;

};

#endif /* NALLOCATOR_ALLOCATEDMEMORY_H_ */
