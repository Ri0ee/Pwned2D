#include "Minkowski.h"

Minkowski_Set::Minkowski_Set()
{
    this->nearestPointToOrigin.a = 0;
    this->nearestPointToOrigin.b = 0;
    this->nearestPointToOriginLength = 0;
}

Minkowski_Set::Minkowski_Set(std::vector<vec2> inVecVectors)
{
    this->vecVectors = inVecVectors;
    this->nearestPointToOrigin.a = 0;
    this->nearestPointToOrigin.b = 0;
    this->nearestPointToOriginLength = 0;
}

Minkowski_Set::~Minkowski_Set()
{
    this->vecVectors.clear();
}

///this = -this
Minkowski_Set Minkowski_Set::operator-()
{
    Minkowski_Set tempMinkowskiSet;
    for(unsigned int i = 0; i < this->vecVectors.size(); i++)
    {
        vec2 tempVec2(-this->vecVectors[i].a, -this->vecVectors[i].b);
        tempMinkowskiSet.vecVectors.insert(tempMinkowskiSet.vecVectors.end(), tempVec2);
    }
    return tempMinkowskiSet;
}

///M1 = this + M2
Minkowski_Set Minkowski_Set::operator+(Minkowski_Set M_Set_1)
{
    Minkowski_Set tempMinkowskiSet;
    for(unsigned int i = 0; i < this->vecVectors.size(); i++)
    {
        for(unsigned int j = 0; j < M_Set_1.vecVectors.size(); j++)
        {
            vec2 tempVec2(this->vecVectors[i].a + M_Set_1.vecVectors[j].a, this->vecVectors[i].b + M_Set_1.vecVectors[j].b);

            unsigned int k = 0;
            do{k++;}
            while((k < tempMinkowskiSet.vecVectors.size()) && ((tempMinkowskiSet.vecVectors[k].a != tempVec2.a) || (tempMinkowskiSet.vecVectors[k].b != tempVec2.b)));

            if(k >= tempMinkowskiSet.vecVectors.size())
                tempMinkowskiSet.vecVectors.insert(tempMinkowskiSet.vecVectors.end(), tempVec2);
        }
    }
    return tempMinkowskiSet;
}

///M1 = this - M2
Minkowski_Set Minkowski_Set::operator-(Minkowski_Set M_Set_1)
{
    return *this + (-M_Set_1);
}

///Finding the (0, 0) in set's difference
bool Minkowski_Set::Intersect(Minkowski_Set M_Set_1)
{
    Minkowski_Set tempMinkowskiSet = *this - M_Set_1;
    std::vector<vec2> vecConvex = Convex(tempMinkowskiSet.vecVectors);
    bool testState = PointCollisionTest(vecConvex, vec2(0, 0));
    if(testState == true)
        this->nearestPointToOrigin = this->GetNearestPoint(vecConvex, this->nearestPointToOriginLength);

    return testState;
}

vec2 Minkowski_Set::GetNearestPoint(std::vector<vec2> vecIn, float &fOut)
{
    vec2 p1 = vecIn[vecIn.size() - 1];
    vec2 p2 = vecIn[0];

    float a = p1.b - p2.b;
    float b = p2.a - p1.a;
    float c = (p1.a * p2.b) - (p2.a * p1.b);
    ///ax + bx + c = 0

    float minx = -(a * c) / ((a * a) + (b * b));
    float miny = -(b * c) / ((a * a) + (b * b));
    float minvecDist = (minx * minx) + (miny * miny);

    for(unsigned int i = 0; i < vecIn.size() - 1; i++)
    {
        a = vecIn[i].b - vecIn[i + 1].a;
        b = vecIn[i + 1].a - vecIn[i].a;
        c = (vecIn[i].a * vecIn[i + 1].b) - (vecIn[i + 1].a * vecIn[i].b);
        float x = -(a * c) / ((a * a) + (b * b));
        float y = -(b * c) / ((a * a) + (b * b));
        float vecDist = (x * x) + (y * y);
        if(vecDist < minvecDist)
        {
            minvecDist = vecDist;
            minx = x;
            miny = y;
        }
    }
    fOut = sqrt(minvecDist);
    return vec2(minx, miny);
}
