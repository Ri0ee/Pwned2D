#pragma once

#include <string>
#include <sstream>
#include <limits>
#include <iostream>
#include <vector>
#include <cmath>

using std::string;
using std::stringstream;
using std::numeric_limits;

string to_string(int num);
string to_string(float num);
string to_string(double num);
bool f_equal(float a, float b);
bool f_equal(float a, float b, float epsilon);

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif // M_PI

#ifndef M_PI_2
#define M_PI_2 (1.57079632679489661923)
#endif // M_PI_2
