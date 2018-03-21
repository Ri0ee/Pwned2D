#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

struct vec2
{
    public:
        float a, b;

        vec2()
        {
            a = 0;
            b = 0;
        }
        vec2(float in1, float in2)
        {
            a = in1;
            b = in2;
        }
};

struct vec3
{
    public:
        float a, b, c;

        vec3()
        {
            a = 0;
            b = 0;
            c = 0;
        }
        vec3(float in1, float in2, float in3)
        {
            a = in1;
            b = in2;
            c = in3;
        }
};

struct clr
{
    public:
        int r, g, b, a;

        clr();
        clr(int in1, int in2, int in3, int in4)
        {
            r = in1;
            g = in2;
            b = in3;
            a = in4;
        }
};

struct color
{
    public:
        int r, g, b, a;
};

struct line
{
    public:
        vec2 v1, v2;

        line();
        line(vec2 in1, vec2 in2)
        {
            v1 = in1;
            v2 = in2;
        }
};

struct collision
{
    public:
        int eID_1, eID_2;
        float ePenetrationDepth;

        collision();
        collision(int in1, int in2, float in3)
        {
            eID_1 = in1;
            eID_2 = in2;
            ePenetrationDepth = in3;
        }
};

