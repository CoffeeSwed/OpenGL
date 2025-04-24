/*
 * NWindow.cpp
 *
 *  Created on: Mar 5, 2025
 *      Author: norman
 */

#include "NWindow.h"

NWindow::NWindow() {
	// TODO Auto-generated constructor stub
	this->debugger = new NDebug((std::ostream*)&std::cout,1);
	this->debugger->inform(NDebugType::INFO, "Debugger start!");
}

NWindow::~NWindow() {
	// TODO Auto-generated destructor stub
	this->debugger->info("Closing program!");
	if(this->debugger != NULL)
		delete(this->debugger);
}

void NWindow::startup(){
	bool initSuccess = glfwInit();
	if(!initSuccess)
		throw std::invalid_argument("glfwInit failed!");
	

	if(glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) && glfwPlatformSupported(GLFW_PLATFORM_X11)) {
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
		this->debugger->inform(NDebugType::INFO,"Using X11 despite the fact WAYLAND is present!");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	this->window = glfwCreateWindow(1920, 1080, "Window", 0,0);
	if(this->window == 0){
		this->debugger->error("Could not create window!");
		throw 0;
	}
	this->debugger->info("Created window, displaying it!");
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(0);
	
	

	
}

void NWindow::run(){
	while(true){
		glfwPollEvents();
		if(glfwWindowShouldClose(this->window)){
			break;
		}
		this->update();
		glfwSwapBuffers(this->window);
	}
	this->debugger->info("Closing window!");
	glfwDestroyWindow(this->window);
	glfwTerminate();
	this->debugger->info("Closed window!");
}

void NWindow::update(){

}

