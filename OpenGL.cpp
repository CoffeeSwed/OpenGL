#include "gtest/gtest.h"
#include "OS/MemoryStatus.h"
#include <iostream>
#include <string>
#include "Window/NWindow.h"
#include "NMatrix/NMatrix.h"
GTEST_API_ int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int res = RUN_ALL_TESTS();
	uint memory = MemoryStatus::VirtualMemoryUsage();
	std::cout << "Virtual Memory usage : " << std::to_string(memory) << "KB\n";
	NWindow window = NWindow();
	window.startup();
	window.run();
}
