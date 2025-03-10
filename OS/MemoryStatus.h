/*
 * MemoryStatus.h
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

//WINDOWS
#ifdef _WIN32
#include "windows.h"
#include "psapi.h"
#endif
//LINUX
#ifndef _WIN32
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <cstdint>
#endif

#ifndef OS_MEMORYSTATUS_H_

#define OS_MEMORYSTATUS_H_

class MemoryStatus {
public:
	static size_t VirtualMemoryUsage();
};

#endif /* OS_MEMORYSTATUS_H_ */
