#include "Utility.h"

string to_string(int num)
{
    stringstream tempStream;
    tempStream << num;
    return tempStream.str();
}

string to_string(float num)
{
    stringstream tempStream;
    tempStream << num;
    return tempStream.str();
}

string to_string(double num)
{
    stringstream tempStream;
    tempStream << num;
    return tempStream.str();
}

bool f_equal(float a, float b)
{
    return fabs(a - b) < numeric_limits<float>::epsilon();
}

bool f_equal(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}

