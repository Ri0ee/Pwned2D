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
freetype::TFreeType ftlib;
gui::TGui guilib;
resources::TResourceManager resmngr;

GLFWwindow* window;

bool keyDown[1000];

TFrameBuffer fbo;
TFrameBuffer fbo_msaa;

///BEGIN

void GameplayRender()
{
    for(unsigned int i = 0; i < Game.m_vecEntities.size(); i++)
        Game.m_vecEntities[i].Draw();

    color text_color{255, 255, 255, 100};

    graphics::ftDrawText("fps: " + to_string(fps), text_color, vec2(0, 10), 10, ftlib);
    graphics::ftDrawText((Game.m_collision_flag?"collision: yes":"collision: no"), text_color, vec2(0, 21), 10, ftlib);
    graphics::ftDrawText("depth: " + to_string(Game.m_collsion_depth), text_color, vec2(0, 32), 10, ftlib);
    graphics::ftDrawText("mouse pos: (" + to_string(mouse_pos.a) + ";" + to_string(mouse_pos.b) + ")", text_color, vec2(0, 44), 10, ftlib);

    graphics::DrawRectangleT(vec2(100, 100), 100, 100, resmngr.m_game_textures.back(), true);
}

void Render()
{
    if(fbo_msaa.m_status && Game.m_msaa)
    {
        fbo_msaa.Bind();
            graphics::Clear();
            GameplayRender();
            guilib.Draw();
        fbo_msaa.Unbind();

        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_msaa.m_framebuffer_id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.m_framebuffer_id);
        glBlitFramebuffer(0, 0, fbo_msaa.m_width, fbo_msaa.m_height, 0, 0, fbo.m_width, fbo.m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
    else
    {
        fbo.Bind();
            graphics::Clear();
            GameplayRender();
            guilib.Draw();
        fbo.Unbind();
    }

    graphics::Clear();
    graphics::DrawRectangleT(0, 0, window_width, window_height, fbo.m_texture_id, false);

    glfwSwapBuffers(window);
}

void button_1_callback()
{
    cout << "Callback function called\n";
}

void InitGL()
{
    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, window_width, window_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    fbo.Create(window_width, window_height);
    fbo_msaa.CreateMultisampled(window_width, window_height, 4);

    glGetIntegerv(GL_MAX_SAMPLES, &max_msaa_samples);
    cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    cout << "Shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    cout << "Maximum MSAA Samples: " << max_msaa_samples << "\n";
}

void InitGUI()
{
    ftlib.Init(current_dir, "Fontin-Regular.ttf");

    color btncolor{77, 0, 57, 50};
    color hl_btncolor{133, 51, 85, 50};
    color fg_btncolor{255, 51, 204, 100};

    vector<vec2> vertex;
    vertex.push_back(vec2(0, 0));    vertex.push_back(vec2(300, 0));
    vertex.push_back(vec2(300, 40)); vertex.push_back(vec2(50, 40));
    TButton button_1(vertex, vec2(window_width - 300, 10), 1, btncolor, fg_btncolor, hl_btncolor, "left", &ftlib);
    TButton button_2(vertex, vec2(window_width - 300, 80), 2, btncolor, fg_btncolor, hl_btncolor, "middle", &ftlib);
    TButton button_3(vertex, vec2(window_width - 300, 150), 3, btncolor, fg_btncolor, hl_btncolor, "right", &ftlib);
    button_1.SetCallback(button_1_callback);
    guilib.AddButton(button_1);
    guilib.AddButton(button_2);
    guilib.AddButton(button_3);
    guilib.m_visible = true;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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
        guilib.Press();
}

bool InitEverything()
{
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

    glewExperimental = GL_TRUE;
    glewInit();

    InitGL();
    InitGUI();

    resmngr.Init(current_dir);

    glfwSetTime(0);
    return true;
}

int main(int argc, char **argv)
{
    SetConsoleTitle("OpenGL debug console");
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
            guilib.CheckCollsions(mouse_pos);

            if(frameCounter >= 0.5)
            {
                fps = frameCount / frameCounter;
                frameCount = 0;
                frameCounter = 0;
            }
            render = true;
        }
        if(render)
        {
            Render();
            frameCount++;
        }
    }

    glfwTerminate();
    return 1;
}
