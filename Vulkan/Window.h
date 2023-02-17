#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:

	const char* windowName;
	int height;
	int width;
	
public:
	GLFWwindow* handle;
	Window* Create(const char *windowName, int clientWidth, int clientHeight);

	void Destroy();

	int getWidth();
	int getHeight();

	void setWidth(int w);
	void setHeight(int h);

};