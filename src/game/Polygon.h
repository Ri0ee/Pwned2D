#pragma once

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "Structures.h"
#include "Minkowski.h"
#include "Render.h"

class TPolygon
{
    public:
        TPolygon();
        TPolygon(int r, int g, int b, int a);
        virtual ~TPolygon();

        void addVertex(vec2 vertex);
        void addVertex(float x, float y);
        void Draw(float X0, float Y0);
        void Rotate(float angle, float X0, float Y0);
        void RotateBase(float angle, float X0, float Y0);

        color m_color;
        Minkowski_Set vecVertex;
        Minkowski_Set vecOutVertex;
};
