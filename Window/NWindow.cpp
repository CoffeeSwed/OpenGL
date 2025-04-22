/*
 * NWindow.cpp
 *
 *  Created on: Mar 5, 2025
 *      Author: norman
 */

#include "NWindow.h"

NWindow::NWindow() {
	// TODO Auto-generated constructor stub

}

NWindow::~NWindow() {
	// TODO Auto-generated destructor stub
}

void NWindow::startup(){
	bool initSuccess = glfwInit();
	if(!initSuccess){
		throw std::invalid_argument("glfwInit failed!");
	}
	else{
		if(glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) && glfwPlatformSupported(GLFW_PLATFORM_X11)) {
            glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

		}else{
			
		}
	}
}

