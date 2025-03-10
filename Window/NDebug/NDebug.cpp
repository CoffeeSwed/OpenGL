/*
 * NDebug.cpp
 *
 *  Created on: Mar 5, 2025
 *      Author: norman
 */

#include "NDebug.h"

void NDebug::NDebugThread(NDebug* inst, std::mutex* l, uint* s){
	while(!*s){
		l->lock();

		if(!*s){

			inst->flush(false);
		}

		l->unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

NDebug::NDebug(std::ostream* stream,uint arraysize) {
	this->stream = stream;
	this->startindex = 0;
	this->records = 0;
	this->protector = new std::mutex();
	this->close = (uint*)malloc(sizeof(uint));
	this->empty = true;
	this->arraysize = arraysize;
	this->messages = (NDebugMessage*)std::malloc(sizeof(NDebugMessage)*(size_t)arraysize);
	*(this->close) = 0;
	this->_thread = std::thread(&NDebug::NDebugThread,this,this->protector,this->close);
	std::cout.flush();

}

void NDebug::flush(bool lock){
	if(lock)
		this->protector->lock();

	while(this->records > 0){
		NDebugMessage* message = this->pop();
		*this->stream << (this->empty ? "" : "\n") << *message->message;
		delete(message->message);
		this->empty = false;
	}
	this->stream->flush();
	if(lock)
		this->protector->unlock();
}

void NDebug::inform(NDebugType t, std::string message, bool lock){

	if(message.find("\n") != std::string::npos){
		if(lock)
			this->protector->lock();
		message = message+"\n";
		this->inform(t,"{",false);
		do{
			std::string partstr = message.substr(0,message.find("\n"));
			message = message.substr(partstr.length()+1);
			this->inform(NDebugType::EMPTY,"	 "+partstr,false);
		}
		while(message.find("\n") != std::string::npos);
		this->inform(NDebugType::EMPTY,"}",false);
		if(lock)
			this->protector->unlock();
	}else{
		if(lock)
			this->protector->lock();

		if(this->records == this->arraysize)
			this->flush(false);

		if(*this->close)
			throw std::runtime_error("Tried to push message while the NDebugger was closing!");
		NDebugMessage entry;
		entry.type = t;
		message = NDebug::getPrefix(t)+" "+message;
		entry.message = new std::string(message);

		this->enque(entry);

		if(lock)
			this->protector->unlock();
	}
}


NDebug::~NDebug() {
	// TODO Auto-generated destructor stub

	this->protector->lock();
	this->flush(false);
	*this->close = 1;
	this->protector->unlock();
	this->_thread.join();
	delete(this->protector);
	free(this->messages);
	free(this->close);


}

std::string NDebug::getPrefix(NDebugType t){
	switch(t){
	case NDebugType::ERROR:
		return "[ERRO]";
	case NDebugType::WARNING:
		return "[WARN]";
	case NDebugType::INFO:
	return "[INFO]";
	case NDebugType::EMPTY:
		return "      ";
	}

	throw std::runtime_error("Unsupported NDebugType!");
}

NDebugMessage* NDebug::pop(){
	if(this->records < 1)
		throw std::runtime_error("Tried to pop list when it was empty!");
	NDebugMessage* messageptr = this->messages + this->startindex;
	this->startindex = (this->startindex + 1) % this->arraysize;
	this->records = this->records - 1;

	return messageptr;
}

void NDebug::enque(NDebugMessage message){
	if(this->records == this->arraysize)
		throw std::runtime_error("Tried to enqueue message when list was full!");
	uint index = (this->startindex + this->records) % this->arraysize;
	NDebugMessage* messageptr = this->messages + index;
	this->records = this->records + 1;
	messageptr->type = message.type;
	messageptr->message = message.message;

}

