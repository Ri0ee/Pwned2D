#include "ConvexHull.h"

vec2 p0;

vec2 GetVectorCoord(vec2 p0, vec2 pDest)
{
    return vec2(pDest.a - p0.a, pDest.b - p0.b);
}

float GetPolarAngle(vec2 p0, float x, float y)
{
    if(y != p0.b)
        return -((x - p0.a) / (y - p0.b));

    if(x < p0.a)
        return -1000000;
    if(x > p0.a)
        return 1000000;
    return 0;
}

float GetPolarAngle(vec2 p0, vec2 p1)
{
    if(p1.b != p0.b)
        return -((p1.a - p0.a) / (p1.b - p0.b));

    if(p1.a < p0.a)
        return -1000000;
    if(p1.a > p0.a)
        return 1000000;
    return 0;
}

float GetDistance(vec2 p0, vec2 pDest)
{
    vec2 xy = GetVectorCoord(p0, pDest);
    return (xy.a * xy.a) + (xy.b * xy.b);
}

int GetOrientation(vec2 p1, vec2 p2, vec2 p3)
{
    float angl = (p2.b - p1.b) * (p3.a - p2.a) - (p3.b - p2.b) * (p2.a - p1.a);
    if(angl == 0) return 0;
    return (angl > 0)?1:2; ///1 - right; 2 - left
}

vec2 nextToTop(std::stack<vec2> &in1)
{
    vec2 p = in1.top();
    in1.pop();
    vec2 res = in1.top();
    in1.push(p);
    return res;
}

std::vector<vec2> Vector(std::stack<vec2> in1)
{
    std::vector<vec2> tVec;
    while(!in1.empty())
    {
        tVec.insert(tVec.end(), in1.top());
        in1.pop();
    }
    return tVec;
}

bool compare(vec2 p1, vec2 p2)
{
    Hull h1, h2;
    h1 = Hull(p1, GetPolarAngle(p0, p1.a, p1.b));
    h2 = Hull(p2, GetPolarAngle(p0, p2.a, p2.b));
    if(h1.angle == h2.angle)
        return (GetDistance(p0, p1) <= GetDistance(p0, p2));
    else
        return (h1.angle > h2.angle);
}

std::vector<vec2> Convex(std::vector<vec2> vecIn)
{
    if(vecIn.size() >= 3)
    {
        ///Bottom most point
        float minY = vecIn[0].b;
        int m = 0;
        for(unsigned int i = 1; i < vecIn.size(); i++)
        {
            float y = vecIn[i].b;
            if((y > minY) || (minY == y && vecIn[i].a < vecIn[m].a))
            {
                m = i;
                minY = y;
            }
        }

        iter_swap(vecIn.begin(), vecIn.begin() + m);
        p0 = vecIn[0];
        std::sort(vecIn.begin() + 1, vecIn.end(), compare);

        ///Remove nearest collinear points
        for(unsigned int i = 1; i < vecIn.size(); i++)
        {
            unsigned int j = i;
            float temp_a1 = GetPolarAngle(p0, vecIn[i]);
            while(j < vecIn.size() - 1)
            {
                j++;
                float temp_a2 = GetPolarAngle(p0, vecIn[j]);
                if(temp_a1 == temp_a2)
                {
                    float temp_dist1 = GetDistance(p0, vecIn[i]);
                    float temp_dist2 = GetDistance(p0, vecIn[j]);
                    if((temp_dist1 == temp_dist2) || (temp_dist1 < temp_dist2))
                    {
                        vecIn.erase(vecIn.begin() + i);
                        j--;
                    }
                }
            }
        }

        ///Build Convex Hull
        std::stack<vec2> S;
        S.push(vecIn[0]);
        S.push(vecIn[1]);
        S.push(vecIn[2]);
        for(unsigned int i = 3; i < vecIn.size(); i++)
        {
            while(GetOrientation(nextToTop(S), S.top(), vecIn[i]) != 1)
                S.pop();

            S.push(vecIn[i]);
        }

        return Vector(S);
    }
    return vecIn;
}
