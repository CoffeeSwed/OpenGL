#ifndef LOGGER_CPP
#define LOGGER_CPP
#include "Logger.h"
NAllocator* Logger::getAllocator(){
	static NAllocator allocator = NAllocator();
	return (NAllocator*)&allocator;
}
#endif