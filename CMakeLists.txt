cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (OpenGL
	VERSION 0.1
	DESCRIPTION "A Hello World Project")

# This project will output an executable file
add_executable(${PROJECT_NAME} OpenGL.cpp 
Window/NWindow.cpp Window/NWindow.h 
Window/NDebug/NDebug.cpp Window/NDebug/NDebug.h
NMatrix/NMatrix.cpp NMatrix/NMatrix.h
NAllocator/NAllocator.cpp NAllocator/NAllocator.h
NAllocator/MemoryChunk.cpp NAllocator/MemoryChunk.h
NAllocator/AllocatedMemory.cpp NAllocator/AllocatedMemory.h

tests/test_NDebug.cpp
tests/test_NMatrix.cpp
OS/MemoryStatus.h OS/MemoryStatus.cpp

)
add_subdirectory(glfw-3.4)


target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)


# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC 
"${PROJECT_BINARY_DIR}"
Window/
Window/NDebug/
)

#Google
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(${PROJECT_NAME} gtest_main)
#add_test(NAME test_NDebug COMMAND ${PROJECT_NAME})
