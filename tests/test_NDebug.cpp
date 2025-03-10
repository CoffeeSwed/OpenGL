#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../Window/NDebug/NDebug.h"
#define TESTS_EXPECTED_FOLDER std::string("./tests/tests_expected/")
#define TESTS_STREAMS std::string("./tests/tests_streams/")

TEST(NDebugTest, positive) {
	for(int j = 0; j < 1;j++){
		std::ofstream file;
		std::string where = TESTS_STREAMS + std::to_string(j)+".txt";
		file.open(where);


		NDebug* debugger = new NDebug(&file,(uint)500);

		debugger->inform(NDebugType::INFO,"0");
		debugger->inform(NDebugType::INFO,"1");
		debugger->inform(NDebugType::INFO,"2");
		debugger->inform(NDebugType::INFO,"3");
		debugger->inform(NDebugType::INFO,"4");
		debugger->inform(NDebugType::INFO, "1 2 3\n4 5 6\n7 8 9");

		for(int i = 0; i < 500000; i++){
				debugger->inform(NDebugType::INFO,std::to_string(i) + " :)");
		}


		delete(debugger);



		file.close();

	}
}
