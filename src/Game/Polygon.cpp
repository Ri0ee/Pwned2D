#include "Polygon.h"

TPolygon::TPolygon()
{
    vecVertex.vecVectors.clear();
    m_Color.r = 100;
    m_Color.g = 100;
    m_Color.b = 100;
    m_Color.a = 100;
}

TPolygon::TPolygon(int r, int g, int b, int a)
{
    vecVertex.vecVectors.clear();
    m_Color.r = r;
    m_Color.g = g;
    m_Color.b = b;
    m_Color.a = a;
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

void TPolygon::Draw(float X0, float Y0)
{
    graphics::DrawPolygon(vecOutVertex.vecVectors, m_Color, X0, Y0, false);
}

void TPolygon::RotateBase(float Angle, float X0, float Y0)
{
    float Ix = cos(Angle);
    float Iy = sin(Angle);
    float Jx = -sin(Angle);
    float Jy = cos(Angle);
    for(unsigned int i = 0; i < vecVertex.vecVectors.size(); i++)
    {
        float X = vecVertex.vecVectors[i].a - (X0 / 2);
        float Y = vecVertex.vecVectors[i].b - (Y0 / 2);
        vecVertex.vecVectors[i].a = (X * Ix + Y * Jx) + (X0 / 2);
        vecVertex.vecVectors[i].b = (X * Iy + Y * Jy) + (Y0 / 2);
    }
}

void TPolygon::Rotate(float Angle, float X0, float Y0)
{
    float Ix = cos(Angle);
    float Iy = sin(Angle);
    float Jx = -sin(Angle);
    float Jy = cos(Angle);
    for(unsigned int i = 0; i < vecVertex.vecVectors.size(); i++)
    {
        float X = vecVertex.vecVectors[i].a - (X0 / 2);
        float Y = vecVertex.vecVectors[i].b - (Y0 / 2);
        vecOutVertex.vecVectors[i].a = (X * Ix + Y * Jx) + (X0 / 2);
        vecOutVertex.vecVectors[i].b = (X * Iy + Y * Jy) + (Y0 / 2);
    }
}
