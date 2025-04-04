/*
 * NAllocator.h
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#ifndef NMATRIX_NALLOCATOR_H_
#define NMATRIX_NALLOCATOR_H_
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "MemoryChunk.h"
#include <algorithm>
#include <sstream>
#include <ios>
class NAllocator {
	std::vector<MemoryChunk*> chunks;
	AllocatedMemory* getAllocation(size_t size);
	size_t calcAllocationSize(size_t size);
	uint_fast64_t empty_chunks = 0;
public:
	///MUST BE LESS THEN CHUNKSLICES
	uint_fast64_t pre_allocate = 16;
	uint_fast64_t allocation_min_size = 8192;
	NAllocator();
	virtual ~NAllocator();
	void* allocate(size_t size);
	void unallocate(void*address);
};

#endif /* NMATRIX_NALLOCATOR_H_ */
