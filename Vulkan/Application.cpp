#define GLAD_VULKAN_IMPLEMENTATION
#include <vulkan/vulkan.h>

#include "Application.h"
#include <stdexcept>
#include <iostream>
#include <vector>

Application* Application::instance = nullptr;

void Application::Create()
{
    instance = new Application;
}

void Application::Destroy()
{
    instance = nullptr;
}

Application& Application::Get()
{
	return *instance;
}

int Application::Run(const char* windowName, int width, int height)
{
    //Quit if the initialization went wrong
    if (!Init(windowName, width, height))
        Quit();

    while (!glfwWindowShouldClose(window->handle))
    {
        glfwPollEvents();
        engine->Update();
        Render();
    }

    vkAPI.DeviceWaitIdle();

    return 0;
}

void Application::Quit()
{
    Release();
}

bool Application::Init(const char* windowName, int width, int height)
{
    window = window->Create(windowName, width, height);
    vkAPI.window = window;
    vkAPI.InitVulkanAPI();

    if (!window)
        return false;

    return true;
}

void Application::Release()
{
    instance->vkAPI.DestroyAPI();
    engine->Destroy();
    window->Destroy();
}

void Application::Render()
{
    vkAPI.DrawFrame();
}
