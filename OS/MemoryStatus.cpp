/*
 * MemoryStatus.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: norman
 */

#include "MemoryStatus.h"

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

size_t MemoryStatus::VirtualMemoryUsage(){
#ifdef _WIN32
PROCESS_MEMORY_COUNTERS_EX pmc;
GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
return virtualMemUsedByMe/1000;
#else
	FILE* file = fopen("/proc/self/status", "r");
	uint_fast64_t result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
#endif
}

