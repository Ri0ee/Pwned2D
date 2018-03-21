#include "TGameEntity.h"

TGameEntity::TGameEntity(string entity_name, TPolygon polygon, vec2 origin, float mass, float acceleration, float rotation_speed)
{
    m_name = entity_name;
    m_x = origin.a;
    m_y = origin.b;
    m_vecPolygon.push_back(polygon);

    m_mass = mass;

    m_acceleration = acceleration;
    m_rotation_speed = rotation_speed;
    m_angle = 0;
    m_velocity = 0;
    m_rotation = 0;

    FindBoudaries();
}

TGameEntity::~TGameEntity()
{
    m_vecPolygon.clear();
}

void TGameEntity::AddShape(TPolygon polygon)
{
    polygon.RotateBase(m_angle, m_width, m_height);
    m_vecPolygon.push_back(polygon);
}

void TGameEntity::Draw()
{
    for(unsigned int i = 0; i < m_vecPolygon.size(); i++)
    {
        m_vecPolygon[i].Rotate(m_angle, m_width, m_height);
        m_vecPolygon[i].Draw(m_x, m_y);
    }
}

void TGameEntity::FindBoudaries()
{
    float MaxW, MaxH;
    float MinW, MinH;
    MinW = m_vecPolygon[0].vecOutVertex.vecVectors[0].a;
    MinH = m_vecPolygon[0].vecOutVertex.vecVectors[0].b;
    for(unsigned int i = 0; i < m_vecPolygon.size(); i++)
    {
        for(unsigned int j = 0; j < m_vecPolygon[i].vecOutVertex.vecVectors.size(); j++)
        {
            MaxW = max(m_vecPolygon[i].vecOutVertex.vecVectors[j].a, MaxW);
            MaxH = max(m_vecPolygon[i].vecOutVertex.vecVectors[j].b, MaxH);
            MinW = min(m_vecPolygon[i].vecOutVertex.vecVectors[j].a, MinW);
            MinH = min(m_vecPolygon[i].vecOutVertex.vecVectors[j].b, MinH);
        }
    }
    m_width = MaxW;
    m_height = MaxH;
    m_x += MinW;
    m_y += MinH;
}
