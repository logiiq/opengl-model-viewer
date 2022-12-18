#include "Time.h"
#include <GLFW/glfw3.h>

double oldTime = 0.0;
double currentTime = 0.0;
double deltaTime = 0.0;

void time_calc(void)
{
	oldTime = currentTime;
	currentTime = glfwGetTime();

	deltaTime = currentTime - oldTime;
}

float time_deltaTimef(void)
{
	return (float)deltaTime;
}

double time_deltaTimed(void)
{
	return deltaTime;
}