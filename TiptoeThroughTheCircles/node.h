#pragma once
#include "point.h"
#include <vector>

using namespace std;

struct Node
{
    int _i;
    int _prev;
    double _x;
    double _y;
    double _dist;
    int _circleIndex;
    vector<int> _neighs;

    Node(int i, Point p, double dist) : _i(i), _prev(-1), _x(p.x), _y(p.y), _dist(dist), _circleIndex(-1), _neighs() {}
    Node(int i, Point p, double dist, int circleIndex) : _i(i), _prev(-1), _x(p.x), _y(p.y), _dist(dist), _circleIndex(circleIndex), _neighs() {}

    void AddNeigh(int i)
    {
        _neighs.push_back(i);
    }
};