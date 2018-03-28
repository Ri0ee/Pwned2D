#include "Polygon.h"

TPolygon::TPolygon()
{
    vecVertex.vecVectors.clear();
    m_color.r = 100;
    m_color.g = 100;
    m_color.b = 100;
    m_color.a = 100;
}

TPolygon::TPolygon(int r, int g, int b, int a)
{
    vecVertex.vecVectors.clear();
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    m_color.a = a;
}

TPolygon::~TPolygon()
{

}

void TPolygon::addVertex(vec2 vertex)
{
    vecVertex.vecVectors.push_back(vertex);
    vecOutVertex.vecVectors.push_back(vertex);
}

void TPolygon::addVertex(float x, float y)
{
    vecVertex.vecVectors.push_back(vec2(x, y));
    vecOutVertex.vecVectors.push_back(vec2(x, y));
}

void TPolygon::RotateBase(float angle, float X0, float Y0)
{
    float Ix = cos(angle);
    float Iy = sin(angle);
    float Jx = -sin(angle);
    float Jy = cos(angle);
    for(unsigned int i = 0; i < vecVertex.vecVectors.size(); i++)
    {
        float X = vecVertex.vecVectors[i].a - (X0 / 2);
        float Y = vecVertex.vecVectors[i].b - (Y0 / 2);
        vecVertex.vecVectors[i].a = (X * Ix + Y * Jx) + (X0 / 2);
        vecVertex.vecVectors[i].b = (X * Iy + Y * Jy) + (Y0 / 2);
    }
}

void TPolygon::Rotate(float angle, float X0, float Y0)
{
    float Ix = cos(angle);
    float Iy = sin(angle);
    float Jx = -sin(angle);
    float Jy = cos(angle);
    for(unsigned int i = 0; i < vecVertex.vecVectors.size(); i++)
    {
        float X = vecVertex.vecVectors[i].a - (X0 / 2);
        float Y = vecVertex.vecVectors[i].b - (Y0 / 2);
        vecOutVertex.vecVectors[i].a = (X * Ix + Y * Jx) + (X0 / 2);
        vecOutVertex.vecVectors[i].b = (X * Iy + Y * Jy) + (Y0 / 2);
    }
}
