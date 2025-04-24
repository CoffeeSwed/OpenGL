/*
 * NDebug.h
 *
 *  Created on: Mar 5, 2025
 *      Author: norman
 */

#ifndef WINDOW_NDEBUG_NDEBUG_H_
#define WINDOW_NDEBUG_NDEBUG_H_
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <chrono>

typedef enum {
	INFO = 0,
		WARNING = 1,
		ERROR = 2,
		EMPTY = 3
} NDebugType;
struct NDebugMessage{
		NDebugType type;
		std::string* message;
	};



class NDebug {
	public:
	NDebug(std::ostream* stream, uint arraysize = 100);
	static void NDebugThread(NDebug* instance, std::mutex* lock, uint* shouldclose);



	virtual ~NDebug();

	void inform(NDebugType, std::string message, bool lock=true);
	void info(std::string message);
	void error(std::string message);
	void warning(std::string message);
	void flush(bool lock=true);

	private:
	std::ostream* stream;
	struct NDebugMessage* messages;
	uint startindex;
	uint records;
	uint arraysize;
	std::mutex* protector;
	uint* close;
	std::thread _thread;
	bool empty;

	static std::string getPrefix(NDebugType type);

	NDebugMessage* pop();
	void enque(NDebugMessage p);

};

#endif /* WINDOW_NDEBUG_NDEBUG_H_ */
