#pragma once

#include "Engine.h"
#include "Window.h"
#include "VulkanAPI.h"

class Application
{
private:
	static Application* instance;
	Engine* engine;
	Window* window;
	VkAPI vkAPI;
	Camera camera;

public:
	
	static void Create();
	static void Destroy();
	static Application& Get();

	int Run(const char* windowName, int width, int height);
	void Quit();

private:
	bool Init(const char* windowName, int width, int height);

	void Release();
	void Render();
};