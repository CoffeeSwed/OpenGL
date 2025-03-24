/*
 * MemoryChunk.h
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#ifndef NALLOCATOR_MEMORYCHUNK_H_
#define NALLOCATOR_MEMORYCHUNK_H_
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "AllocatedMemory.h"
#include <iostream>

#define CHUNKSLICES 64

class MemoryChunk {
	void* location;
	size_t size;

public:
	size_t allocations = 0;
	AllocatedMemory* allocate(size_t size);
	void unallocate(AllocatedMemory* allocation);
	MemoryChunk(size_t size);
	virtual ~MemoryChunk();
};

#endif /* NALLOCATOR_MEMORYCHUNK_H_ */
