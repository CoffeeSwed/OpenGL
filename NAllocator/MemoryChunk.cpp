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

		if(allocation->size - allocation->size_allocated >= size+sizeof(AllocatedMemory)){
			this->allocations++;

			if(allocation->size_allocated != 0){
				AllocatedMemory* previous = allocation;
				allocation = (AllocatedMemory*)((uint_fast64_t)previous+(uint_fast64_t)previous->size_allocated);
				allocation->size = previous->size - previous->size_allocated;
				previous->size = previous->size_allocated;
				allocation->prev = previous;
				allocation->size_allocated = size+sizeof(AllocatedMemory);
				allocation->owner = previous->owner;
				AllocatedMemory* next = (AllocatedMemory*)((uint_fast64_t)allocation+(uint_fast64_t)allocation->size);
				if((uint_fast64_t)next < ((uint_fast64_t)this->location+(uint_fast64_t)this->size)){
					next->prev = allocation;
				}
				return allocation;
			}else{
				allocation->size_allocated = size+sizeof(AllocatedMemory);
				return allocation;
			}
		}
		
		
		if(allocation->size == 0)
			break;
		allocation = (AllocatedMemory*)((uint_fast64_t)allocation+allocation->size);
	}

	return NULL;
}

void MemoryChunk::unallocate(AllocatedMemory* allocation){
	if(allocation == this->location){
		allocation->size_allocated = 0;
	}else{
		AllocatedMemory* next = (AllocatedMemory*)((uint_fast64_t)allocation+(uint_fast64_t)allocation->size);
		if((uint_fast64_t)next < ((uint_fast64_t)this->location+(uint_fast64_t)this->size)){
			next->prev = allocation->prev;
		}
		allocation->prev->size += allocation->size;
		//std::cout << "previous : " << std::to_string((uint_fast64_t)allocation->prev) << "\n";
	}
	this->allocations--;
	
}
