/*
 * NAllocator.cpp
 *
 *  Created on: Mar 15, 2025
 *      Author: norman
 */

#include "NAllocator.h"

NAllocator::NAllocator() {
	// TODO Auto-generated constructor stub
	this->chunks = std::vector<MemoryChunk*>();
	this->empty_chunks = 0;
}

size_t NAllocator::calcAllocationSize(size_t size){
	size = size*this->pre_allocate;
	if(size < this->allocation_min_size)
		size = this->allocation_min_size;
	return size;
}

AllocatedMemory* NAllocator::getAllocation(size_t size){


	for(uint_fast64_t index = this->chunks.size(); index > 0;index--){
		AllocatedMemory* piece = this->chunks[index-1]->allocate(size);
		if(piece != NULL){
			if(this->chunks[index-1]->allocations == 1)
				this->empty_chunks = this->empty_chunks - 1;

			return piece;
		}
	}
	MemoryChunk* chunk = new MemoryChunk(this->calcAllocationSize(size));
	this->chunks.push_back(chunk);
	return chunk->allocate(size);
}

NAllocator::~NAllocator() {
	// TODO Auto-generated destructor stub
	while(this->chunks.size() > 0){
		MemoryChunk* chunk = this->chunks[this->chunks.size()-1];
		std::vector<MemoryChunk*>::iterator position = std::find(this->chunks.begin(), this->chunks.end(), chunk);
		if(position != this->chunks.end()){
			this->chunks.erase(position);
		}
		delete(chunk);
	}
}

void* NAllocator::allocate(size_t size){
	uint_fast64_t pos = (uint_fast64_t)this->getAllocation(size);
	AllocatedMemory* memorypart = (AllocatedMemory*)pos;

	//std::cout << "Allocated : " << std::to_string(pos) << "\n";

	pos += sizeof(AllocatedMemory);

	//std::cout << "Memorypart : \n" << memorypart->toString() << "\n";

	return (void*)pos;
}

void NAllocator::unallocate(void*_address){
	uint_fast64_t address = (uint_fast64_t)_address;
	if(address != 0){
		//std::cout << "Unallocated : " << std::to_string(address) << "\n";

		address = address - (uint_fast64_t)sizeof(AllocatedMemory);

		AllocatedMemory* alloc = (AllocatedMemory*)address;

		//std::cout << "Memorypart : \n" << alloc->toString() << "\n";
		MemoryChunk* chunk = (MemoryChunk*)alloc->owner;
		chunk->unallocate(alloc);
		if(chunk->allocations == 0)
			this->empty_chunks++;

		if(chunk->allocations == 0 && this->empty_chunks > 1){
			std::vector<MemoryChunk*>::iterator position = std::find(this->chunks.begin(), this->chunks.end(), chunk);
			if(position != this->chunks.end()){
				this->chunks.erase(position);
			}
			delete(chunk);
			this->empty_chunks--;
		}
		
	}
	


}
