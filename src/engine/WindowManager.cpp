#include "WindowManager.h"

namespace window
{
	TWindowManager::TWindowManager(string window_name, int window_width, int window_height)
	{
		m_window_name = window_name;
		m_window_height = window_height;
		m_window_width = window_width;
		m_status = false;
		if(glfwInit() == GLFW_TRUE)
		{
			m_status = true;
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
			glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

			m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_name, 0, 0);
			if(m_window == 0)
			{
				cout << "Failed to create window" << endl;
				glfwTerminate();
				m_status = false;
			}
		}
		else cout << "Failed to initialize GLFW3" << endl;
	}

	TWindowManager::~TWindowManager()
	{
		if(!m_status)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}
}
