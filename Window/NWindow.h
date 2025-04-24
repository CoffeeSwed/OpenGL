/*
 * NWindow.h
 *
 *  Created on: Mar 5, 2025
 *      Author: norman
 */

#ifndef WINDOW_NWINDOW_H_
#define WINDOW_NWINDOW_H_
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "NDebug/NDebug.h"
#include <cstdio>


class NWindow {
public:
	NWindow();
	void startup();
	~NWindow();
	void run();
	virtual void update();
	NDebug* debugger;
	GLFWwindow* window;
};

#endif /* WINDOW_NWINDOW_H_ */
