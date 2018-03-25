#include "Game.h"

namespace game
{
    TGame::TGame(){}

    TGame::~TGame(){}

    void TGame::Init(graphics::TRenderer *rndr, gui::TGui *gui, resources::TResourceManager *resmngr)
    {
        m_vecCollisions.clear();
        m_msaa = false;
        m_collision_flag = false;
        m_collsion_depth = 0;
        m_renderer_state = false;
        m_gui_state = false;
        m_render_needed = false;

        TPolygon Triangle(255, 87, 51, 100);
        Triangle.addVertex(0, 100);
        Triangle.addVertex(100, 100);
        Triangle.addVertex(50, 0);
        AddEntity(TGameEntity("Player", Triangle, vec2(10, 200), 1, 10, M_PI / 180));

        SetRenderer(rndr);
        SetGui(gui);
        SetResourceManager(resmngr);
    }

    void TGame::SetRenderer(graphics::TRenderer *rndr)
    {
        m_renderer = rndr;
        m_renderer_state = true;
    }

    void TGame::SetGui(gui::TGui *gui)
    {
        m_gui = gui;

        //m_gui->GetButton("Start").SetCallback(&StartGame);

        m_gui_state = true;
    }

    void TGame::SetResourceManager(resources::TResourceManager *resmngr)
    {
        m_resource_manager = resmngr;
        m_resource_manager_state = true;
    }

    void TGame::StartGame(void) ///Button "Start" callback
    {
        cout << "Game should be started\n";
    }

    void TGame::AddEntity(TGameEntity entity)
    {
        m_vecEntities.push_back(entity);
    }

    TGameEntity& TGame::GetEntity(string entity_name)
    {
        for(unsigned int i = 0; i < m_vecEntities.size(); i++)
            if(m_vecEntities[i].m_name == entity_name)
                return m_vecEntities[i];
        return m_vecEntities[0];
    }

    int TGame::FindForwardCollisionM(int eID1, int eID2, float deltaTime, float &penetrationDepth)
    {
        TGameEntity e1 = m_vecEntities[eID1];
        TGameEntity e2 = m_vecEntities[eID2];

        TPolygon tempE1 = e1.m_vecPolygon[0];
        TPolygon tempE2 = e2.m_vecPolygon[0];

        float X0_t = e1.m_x + (e1.m_velocity + e1.m_acceleration * deltaTime) * cos(e1.m_angle) * deltaTime;
        float Y0_t = e1.m_y + (e1.m_velocity + e1.m_acceleration * deltaTime) * sin(e1.m_angle) * deltaTime;

        float e2_X0_t = e2.m_x + (e2.m_velocity + e2.m_acceleration * deltaTime) * cos(e2.m_angle) * deltaTime;
        float e2_Y0_t = e2.m_y + (e2.m_velocity + e2.m_acceleration * deltaTime) * sin(e2.m_angle) * deltaTime;

        for(unsigned int i = 0; i < tempE1.vecOutVertex.vecVectors.size(); i++)
        {
            tempE1.vecOutVertex.vecVectors[i].a += X0_t;
            tempE1.vecOutVertex.vecVectors[i].b += Y0_t;
        }

        for(unsigned int i = 0; i < tempE2.vecOutVertex.vecVectors.size(); i++)
        {
            tempE2.vecOutVertex.vecVectors[i].a += e2_X0_t;
            tempE2.vecOutVertex.vecVectors[i].b += e2_Y0_t;
        }

        bool ans = tempE1.vecOutVertex.Intersect(tempE2.vecOutVertex);
        if(ans) penetrationDepth = tempE1.vecOutVertex.nearestPointToOriginLength;
        return ans;
    }

    void TGame::Input(bool* keys)
    {
        if(keys[GLFW_KEY_A])
            GetEntity("Player").m_rotation = -GetEntity("Player").m_rotation_speed;

        if(keys[GLFW_KEY_D])
            GetEntity("Player").m_rotation = GetEntity("Player").m_rotation_speed;

        if(keys[GLFW_KEY_W])
            GetEntity("Player").m_velocity += GetEntity("Player").m_acceleration;

        if(keys[GLFW_KEY_S])
            GetEntity("Player").m_velocity -= GetEntity("Player").m_acceleration;

        if(keys[GLFW_KEY_M])
            if(m_sleep_time > 50)
            {
                m_msaa = !m_msaa;
                m_sleep_time = 0;
            }
    }

    void TGame::Update(float delta_time)
    {
        m_collision_flag = false;
        m_collsion_depth = 0;
        m_vecCollisions.clear();
        m_sleep_time++;

        ///Looking for Collision
        for(unsigned int i = 0; i < m_vecEntities.size(); i++)
        {
            for(unsigned int j = i + 1; j < m_vecEntities.size(); j++)
            {
                float tempPenetrationDepth = 0;
                if(FindForwardCollisionM(i, j, delta_time, tempPenetrationDepth))
                {
                    collision tempCollision(i, j, tempPenetrationDepth);
                    m_vecCollisions.push_back(tempCollision);
                    m_collision_flag = true;
                    m_collsion_depth = tempPenetrationDepth;
                }
            }
        }

        ///Position Processing
        for(vector<TGameEntity>::iterator ent = m_vecEntities.begin(); ent != m_vecEntities.end(); ++ent)
        {
            ent->m_angle += ent->m_rotation;
            ent->m_velocity = ent->m_velocity - ent->m_velocity * DECIPATON;

            float rA = ent->m_angle - M_PI_2;
            ent->m_rotation = 0;

            float VelocityX = ent->m_velocity * cos(rA);
            float VelocityY = ent->m_velocity * sin(rA);

            ent->m_x += VelocityX * delta_time;
            ent->m_y += VelocityY * delta_time;
        }

        ///Game entity and gui element render
        if(m_render_needed)
        {
            m_renderer->BeginRender();
            if(m_renderer_state)
            {
                for(unsigned int i = 0; i < m_vecEntities.size(); i++)
                {
                    for(unsigned int j = 0; j < m_vecEntities[i].m_vecPolygon.size(); i++)
                    {
                        m_vecEntities[i].Rotate();
                        m_renderer->DrawPolygon(m_vecEntities[i].m_vecPolygon[j].vecOutVertex.vecVectors, m_vecEntities[i].m_vecPolygon[j].m_color, vec2(m_vecEntities[i].m_x, m_vecEntities[i].m_y), false);
                    }
                }
                if(m_gui_state)
                {
                    m_gui->Draw();
                }
            }
            m_renderer->EndRender();
            m_render_needed = false;
        }
    }
}
