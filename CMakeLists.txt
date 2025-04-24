cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 20)
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
Graphics/Translations.cpp Graphics/Translations.h
Graphics/GLUtils.cpp Graphics/GLUtils.h
Graphics/GLProgram.cpp Graphics/GLProgram.h
Graphics/GLShader.cpp Graphics/GLShader.h
OS/NFiles.cpp OS/NFiles.h


tests/test_NDebug.cpp
tests/test_NMatrix.cpp
OS/MemoryStatus.h OS/MemoryStatus.cpp
tests/tests_Translations.cpp
tests/tests_OS.cpp

)
add_subdirectory(glfw-3.4)
file(GLOB_RECURSE THE_DIRECTORIES LIST_DIRECTORIES TRUE CONFIGURE_DEPENDS
  "resources/*" 
)
SET(dirlist "")
foreach(dir ${THE_DIRECTORIES})
  if(IS_DIRECTORY ${dir})
    LIST(APPEND dirlist ${dir})
  else()
    continue()
  endif()
endforeach()

FILE(COPY ${dirlist} DESTINATION "resources")
file(GLOB THE_DIRECTORIES LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS
  "resources/*" 
)
FILE(COPY ${THE_DIRECTORIES} DESTINATION "resources")

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
