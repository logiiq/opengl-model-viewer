#include "Input.h"
#include "Camera.h"
#include "Time.h"

GLFWwindow *getWindow(void); // window handle function proto
Camera_t *getCamera(void);

static float spd = 6.0f;
static float mvSpeed;

static int drawMode = 0;

// Callback prototypes
static void calc_offset(void);
static void keycallback(GLFWwindow *window, int scancode, int action, int key, int mods);
static void mposcallback(GLFWwindow *window, double xpos, double ypos);

void input_init(void)
{
	glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Disable cursor

	glfwSetKeyCallback(getWindow(), &keycallback);
	glfwSetCursorPosCallback(getWindow(), &mposcallback);
}

void input_process(void)
{
	calc_offset();

	mvSpeed = spd * time_deltaTimef();

	if (glfwGetKey(getWindow(), GLFW_KEY_LEFT))
	{
		camera_rot(getCamera(), -mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_RIGHT))
	{
		camera_rot(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_A))
	{
		camera_left(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_D))
	{
		camera_right(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_W))
	{
		camera_forward(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_S))
	{
		camera_backward(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_SPACE))
	{
		camera_up(getCamera(), mvSpeed);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_LEFT_CONTROL))
	{
		camera_down(getCamera(), mvSpeed);
	}
	
}

static float oldX = 0.0f;
static float oldY = 0.0f;
static float sens = 0.1f;

static float m_pos[2]; // Actual mouse position on screen
static float m_off[2]; // Mouse offset from last known position

static int first_mouse = 1;

static void mposcallback(GLFWwindow *window, double xpos, double ypos)
{
	if (first_mouse)
	{
		oldX = (float)xpos;
		oldY = (float)ypos;
		first_mouse = 0;
	}

	m_pos[0] = (float) xpos;
	m_pos[1] = (float) ypos;
}

static void calc_offset(void)
{
	m_off[0] = sens * ((float)m_pos[0] - oldX);
	m_off[1] = sens * (oldY - (float)m_pos[1]);

	oldX = (float)m_pos[0];
	oldY = (float)m_pos[1];
}

const float *get_m_off(void)
{
	return &m_off;
}

const float *get_m_pos(void)
{
	return &m_pos;
}

static void keycallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(getWindow(), GLFW_TRUE);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		drawMode = !drawMode;

		if (drawMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		spd *= 2.0f;
	}
	else
	{
		spd = 6.0f;
	}
}