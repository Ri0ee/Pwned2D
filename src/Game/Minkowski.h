#pragma once

#include <vector>

#include "Structures.h"
#include "ConvexHull.h"
#include "PointCollision.h"
#include "Utility.h"

class Minkowski_Set
{
    public:
        Minkowski_Set();
        Minkowski_Set(std::vector<vec2> inVecVectors);
        virtual ~Minkowski_Set();

        Minkowski_Set operator-();
        Minkowski_Set operator-(Minkowski_Set M_Set_1);
        Minkowski_Set operator+(Minkowski_Set M_Set_1);

        bool Intersect(Minkowski_Set M_Set_1);
        vec2 GetNearestPoint(std::vector<vec2> vecIn, float &fOut);

        vec2 nearestPointToOrigin;
        float nearestPointToOriginLength;

        std::vector<vec2> vecVectors;
};
