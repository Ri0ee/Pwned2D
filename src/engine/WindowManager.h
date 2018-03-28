#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;

namespace window
{
	class TWindowManager
	{
        public:
            TWindowManager();
            virtual ~TWindowManager();

            GLFWwindow* m_window;
            string m_window_name;
            int m_window_width;
            int m_window_height;
            bool m_status;
	};
}
