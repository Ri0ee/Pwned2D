#include "InputManager.h"

namespace input
{
	TInputManager::TInputManager(window::TWindowManager* windowmngr)
	{
	    m_mouse_is_pressed = false;
	    m_mouse_is_released = false;
	    m_mouse_pos = vec2(0, 0);
	    m_key_state.resize(1000);
	    m_window_manager = windowmngr;

		glfwSetKeyCallback(m_window_manager->m_window, &key_callback);
        glfwSetCursorPosCallback(m_window_manager->m_window, &mouse_move_callback);
        glfwSetMouseButtonCallback(m_window_manager->m_window, &mouse_button_callback);
        cout << "Input manager constructor called" << endl;
	}

	TInputManager::~TInputManager()
	{
        cout << "Input manager destructor called" << endl;
	}

	void TInputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if(action == GLFW_PRESS)
		{
			if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(m_window_manager->m_window, GL_TRUE);
			m_key_state[key] = true;
			return;
		}

		if(action == GLFW_RELEASE)
        {
            m_key_state[key] = false;
            return;
        }
	}

	void TInputManager::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
	{
		m_mouse_pos.a = xpos;
		m_mouse_pos.b = ypos;
	}

	void TInputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
	    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            m_mouse_is_pressed = true;
            m_mouse_is_released = false;
            return;
        }
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            m_mouse_is_released = true;
            m_mouse_is_pressed = false;
            return;
        }
	}
}
