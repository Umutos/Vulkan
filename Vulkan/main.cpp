#define GLAD_VULKAN_IMPLEMENTATION
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include "Application.h"

int main() 
{
	Application::Create();
	Application app = Application::Get();

	try
	{
		app.Run("Vulkan", 800, 600);
	}
	catch (const std::exception& except) // For any problems
	{
		std::cerr << except.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
	
}
