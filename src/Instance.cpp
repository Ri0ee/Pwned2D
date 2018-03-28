#include "Instance.h"

TInstance::TInstance(string current_dir, string program_name, int window_width, int window_height)
{
    m_current_dir = current_dir;

    Window_Instance = new window::TWindowManager(program_name, window_width, window_height);
    Render_Instance = new graphics::TRenderer(&Window_Instance);
    FT_Instance = new freetype::TFreeType(current_dir, "Fontin-Regular.ttf");
    RM_Instance = new resources::TResourceManager(current_dir);
    IM_Instance = new input::TInputManager(&Window_Instance);
    GUI_Instance = new gui::TGui(&FT_Instance, &Render_Instance, &IM_Instance);
    Game_Instance = new game::TGame(&Render_Instance, &GUI_Instance, &RM_Instance, &IM_Instance);
}

TInstance::~TInstance()
{
    delete Window_Instance;
    delete FT_Instance;
    delete GUI_Instance;
    delete RM_Instance;
    delete IM_Instance;
    delete GUI_Instance;
    delete Game_Instance;
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
