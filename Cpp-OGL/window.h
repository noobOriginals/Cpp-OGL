#pragma once
#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

unsigned int windowGetCount();
void windowEnableCallouts();
void windowDisableCallouts();

class Window {
public:
	Window() {title = ""; address = 0;}
	Window(int width, int height, string title);
	void flush();
	void enableVSync();
	void disableVSync();
	void hideMouse();
	void showMouse();
	void getSize(int* width, int* height);
	void setFramebufferSizeCallback(void(*func)(GLFWwindow* window, int width, int height));
	void setCursorPosCallback(void(*func)(GLFWwindow* window, double xpos, double ypos));
	GLFWwindow* getAddress();
	void show();
	void hide();
	void makeCurrentContext();
	bool shouldClose();
	bool keyPressed(short key);
	bool mousePressed(short button);
	~Window();

private:
	string title;
	GLFWwindow* address;
};

#endif