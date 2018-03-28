#include "InputManager.h"
namespace input
{
	TInputManager::TInputManager(window::TWindowManager* windowmngr)
	{
		glfwSetKeyCallback(windowmngr->m_window, key_callback);
        glfwSetCursorPosCallback(windowmngr->m_window, mouse_move_callback);
        glfwSetMouseButtonCallback(windowmngr->m_window, mouse_button_callback);
	}

	TInputManager::~TInputManager()
	{

	}

	void TInputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if(action == GLFW_PRESS)
		{
			if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GL_TRUE);
			keyDown[key] = true;
			return;
		}

		if(action == GLFW_RELEASE)
			keyDown[key] = false;
	}

	void TInputManager::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mouse_pos.a = xpos;
		mouse_pos.b = ypos;
	}

	void TInputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
			GUIlib.Press();
	}
}
