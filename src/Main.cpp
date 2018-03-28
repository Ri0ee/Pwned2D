#include "Utility.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ETime.h"
#include "FrameBuffer.h"

#include "Game.h"
#include "Render.h"
#include "FreeType.h"
#include "Gui.h"
#include "ResourceManager.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

double fps             = 0;
int window_width       = 1280;
int window_height      = 720;
int max_msaa_samples   = 0;
const char* window_name= "OpenGLEngine";

vec2 mouse_pos;
string current_dir;

game::TGame Game;
gui::TGui GUIlib;
freetype::TFreeType FTlib;
resources::TResourceManager Resource_manager;
graphics::TRenderer Renderer;

GLFWwindow* window;

bool keyDown[1000];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_pos.a = xpos;
	mouse_pos.b = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		GUIlib.Press();
}

bool InitEverything()
{
	///Graphics initialization
	if(glfwInit() != GLFW_TRUE)
	{
		cout << "Failed to initialize GLFW3\n";
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	window = glfwCreateWindow(window_width, window_height, window_name, 0, 0);
	if(window == 0)
	{
		cout << "Failed to create window\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	///Module initialization
	FTlib.Init(current_dir, "Fontin-Regular.ttf"); ///Working fine
	Renderer.Init(window, window_width, window_height); ///Might be better
	GUIlib.Init(&FTlib, &Renderer, window_width, window_height); ///TODO: fix something here
	Resource_manager.Init(current_dir); ///Working fine
	Game.Init(&Renderer, &GUIlib, &Resource_manager);

	glfwSetTime(0);
	return true;
}

int main(int argc, char **argv)
{
	string argv_str = argv[0];
	current_dir = argv_str.substr(0, argv_str.find_last_of("\\") + 1);
	cout << "current_dir: " << current_dir << "\n";

	if(!InitEverything())
		return -1;

	double unprocessedTime = 0.0;
	double deltaTime       = 1.0/150.0;
	double frameCounter    = 0;
	double lastTime        = glfwGetTime();
	int    frameCount      = 0;

	while(!glfwWindowShouldClose(window)) ///Game loop
	{
		glfwPollEvents();
		bool render = false;
		double startTime = glfwGetTime();
		double passedTime = startTime - lastTime;
		lastTime = glfwGetTime();

		unprocessedTime+=passedTime;
		frameCounter+=passedTime;

		while(unprocessedTime > deltaTime)
		{
			unprocessedTime-=deltaTime;

			Game.Input(keyDown);
			Game.Update(deltaTime);
			GUIlib.CheckCollsions(mouse_pos);

			if(frameCounter >= 0.5)
			{
				fps = frameCount / frameCounter;
				frameCount = 0;
				frameCounter = 0;
			}
			render = true;
		}
		Game.m_render_needed = true;
		frameCount++;
	}

	glfwTerminate();
	return 1;
}
