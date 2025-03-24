/*
 * MemoryChunk.cpp
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#include "MemoryChunk.h"

MemoryChunk::MemoryChunk(size_t size) {
	// TODO Auto-generated constructor stub
	size = size + (size_t)CHUNKSLICES*sizeof(AllocatedMemory);
	this->location = std::malloc(size);
	this->size = size;
	AllocatedMemory* allocation = (AllocatedMemory*)this->location;
	allocation->size = this->size;
	allocation->size_allocated = 0;
	allocation->prev = NULL;
	allocation->owner = (void*)this;
}

MemoryChunk::~MemoryChunk() {
	if(this->location != NULL)
		free(this->location);
	this->location = NULL;
}

AllocatedMemory* MemoryChunk::allocate(size_t size){
	AllocatedMemory* allocation = (AllocatedMemory*)this->location;

	while((uint_fast64_t)allocation < ((uint_fast64_t)this->location+(uint_fast64_t)this->size)){
		/*IF not allocated!*/
		if(allocation->size_allocated == 0)
		{
			//Has enough space to allocate wished size plus overhead
			if(allocation->size >= sizeof(AllocatedMemory) + size){

				size_t remains = allocation->size - size - sizeof(AllocatedMemory);
				allocation->size_allocated = size + sizeof(AllocatedMemory);
				allocation->size = allocation->size_allocated;

				AllocatedMemory* next = (AllocatedMemory*)((uint_fast64_t)allocation+allocation->size);
				next->size_allocated = 0;
				next->size = remains;
				next->prev = allocation;
				next->owner = allocation->owner;
				this->allocations += 1;
				return allocation;
			}
		}

		allocation = (AllocatedMemory*)((uint_fast64_t)allocation+allocation->size);
	}

	return NULL;
}

void MemoryChunk::unallocate(AllocatedMemory* allocation){

}
