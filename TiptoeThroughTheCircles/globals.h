#pragma once
#include "circle.h"
#include <vector>

using namespace std;

static Point a;
static Point b;
static vector<Circle> c;

static double expectation;

static int segCount = 5;
static const double _pi = 3.14159265358979323846;
static const double _inf = 123123;
static const double _maxError = 1e-8;

static unsigned int windowWidth = 1200;
static unsigned int windowHeight = 900;