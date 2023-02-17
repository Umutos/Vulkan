#include "Window.h"
#include <iostream>
#include "VulkanAPI.h"

Window* Window::Create(const char *windowName, int clientWidth, int clientHeight)
{
	Window* window = new Window;

	if (!glfwInit())
	{
		std::cerr << "Echec de l'initialisation de GLFW" << std::endl;
		return nullptr;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window->handle = glfwCreateWindow(clientWidth, clientHeight, windowName, nullptr, nullptr);

	window->windowName = windowName;
	window->width = clientWidth;
	window->height = clientHeight;

	return window;
}

void Window::Destroy()
{
	glfwDestroyWindow(handle);
	glfwTerminate();
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

void Window::setWidth(int w)
{
	width = w;
}

void Window::setHeight(int h)
{
	height = h;
}
