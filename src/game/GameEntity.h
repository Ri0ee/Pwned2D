#pragma once

#include <vector>
#include <iostream>

#include "Polygon.h"
#include "Structures.h"
#include "Logger.h"

using std::vector;
using std::string;

class TGameEntity
{
    public:
        TGameEntity(string entity_name, TPolygon polygon, vec2 origin, float mass, float acceleration, float rotation_speed);
        virtual ~TGameEntity();

        void AddShape(TPolygon polygon);
        void Rotate();
        void FindBoudaries();

        string m_name;
        int m_id;
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        float m_velocity;
        float m_acceleration;
        float m_angle;
        float m_rotation_speed;
        float m_rotation;
        float m_mass;
        vector<TPolygon> m_vecPolygon;
};
