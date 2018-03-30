#include "Instance.h"

TInstance::TInstance(string current_dir, string program_name, int window_width, int window_height)
{
    m_current_dir = current_dir;
    m_should_finish = false;

    Window_Instance = new window::TWindowManager(program_name, window_width, window_height);
    if(Window_Instance->m_status)
    {
        Input_Manager_Instance = new input::TInputManager(Window_Instance);
        Render_Instance = new graphics::TRenderer(Window_Instance);

        FreeType_Instance = new freetype::TFreeType(current_dir, "Fontin-Regular.ttf");
        Resource_Manager_Instance = new resources::TResourceManager(current_dir); ///Needs GLEW to be initialized

        GUI_Instance = new gui::TGui(FreeType_Instance, Render_Instance, Input_Manager_Instance);
        Game_Instance = new game::TGame(Render_Instance, GUI_Instance, Resource_Manager_Instance, Input_Manager_Instance);
    }
    else m_status = false;
}

TInstance::~TInstance()
{
    if(Window_Instance->m_status)
    {
        delete Window_Instance;
        delete FreeType_Instance;
        delete GUI_Instance;
        delete Resource_Manager_Instance;
        delete Input_Manager_Instance;
        delete GUI_Instance;
        delete Game_Instance;
    }
    else delete Window_Instance;
}

void MainLoop()
{
    while(!m_should_finish)
	{
		glfwPollEvents();
		double startTime = GetTime();
		double passedTime = startTime - lastTime;
		lastTime = GetTime();

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
}
