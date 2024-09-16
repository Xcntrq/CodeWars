#pragma once
#include "globals.h"
#include "node.h"
#include "visualizer.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace solution2
{
    struct Graph
    {
        const vector<Circle>& _c;
        const int _segCount;

        double _lenght;

        Point _a;
        Point _b;
        vector<Node> _nodes;

        Graph(Point a, Point b, const vector<Circle>& c, int segCount) : _a(a), _b(b), _c(c), _segCount(segCount), _nodes()
        {
            AddPoint(_a, 0);
            ProcessCircles();
            AddPoint(_b, _inf);
            _lenght = Solve();
        }

        void AddPoint(Point p, double dist)
        {
            Node newNode(_nodes.size(), p, dist);
            ConnectNewNode(newNode);
            _nodes.push_back(newNode);
        }

        void ConnectNewNode(Node& newNode)
        {
            for (Node& node : _nodes)
            {
                if (IsLineValid(newNode, node))
                {
                    newNode.AddNeigh(node._i);
                    node.AddNeigh(newNode._i);
                }
            }
        }

        bool IsLineValid(Node& A, Node& B) const
        {
            for (const Circle& c : _c)
            {
                Point A_translated = { A._x - c.ctr.x, A._y - c.ctr.y };
                Point B_translated = { B._x - c.ctr.x, B._y - c.ctr.y };

                double dx = B_translated.x - A_translated.x;
                double dy = B_translated.y - A_translated.y;

                double A_coeff = dx * dx + dy * dy;
                double B_coeff = 2 * (A_translated.x * dx + A_translated.y * dy);
                double C_coeff = A_translated.x * A_translated.x + A_translated.y * A_translated.y - c.r * c.r;

                double discriminant = B_coeff * B_coeff - 4 * A_coeff * C_coeff;

                if (discriminant > 0)
                {
                    double sqrt_discriminant = sqrt(discriminant);
                    double t1 = (-B_coeff - sqrt_discriminant) / (2 * A_coeff);
                    double t2 = (-B_coeff + sqrt_discriminant) / (2 * A_coeff);

                    bool intersectsAtT1 = (t1 >= -_maxError && t1 <= 1.0 + _maxError);
                    bool intersectsAtT2 = (t2 >= -_maxError && t2 <= 1.0 + _maxError);

                    if (intersectsAtT1 && intersectsAtT2)
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        void ProcessCircles()
        {
            for (size_t j = 0; j < _c.size(); j++)
            {
                const Circle& c = _c[j];
                vector<bool> iExists;
                vector<Node> newNodes;
                for (int i = 0; i < _segCount; i++)
                {
                    double angleStep = 2 * _pi / _segCount;
                    double x = c.ctr.x + c.r * sin(angleStep * i);
                    double y = c.ctr.y + c.r * cos(angleStep * i);
                    Point p(x, y);

                    iExists.push_back(!IsPointInsideAnyCircle(p));
                    if (iExists[i])
                    {
                        Node node(_nodes.size() + newNodes.size(), p, _inf, j);

                        if ((i > 0) && iExists[i - 1])
                        {
                            node.AddNeigh(newNodes[newNodes.size() - 1]._i);
                            newNodes[newNodes.size() - 1].AddNeigh(node._i);
                        }

                        if ((i == _segCount - 1) && iExists[0])
                        {
                            node.AddNeigh(newNodes[0]._i);
                            newNodes[0].AddNeigh(node._i);
                        }

                        newNodes.push_back(node);
                    }
                }

                for (Node& newNode : newNodes)
                {
                    ConnectNewNode(newNode);
                }

                for (Node& newNode : newNodes)
                {
                    _nodes.push_back(newNode);
                }
            }
        }

        bool IsPointInsideAnyCircle(Point p) const
        {
            for (const Circle& c : _c)
            {
                double l1 = (c.ctr.x - p.x);
                double l2 = (c.ctr.y - p.y);
                l1 *= l1;
                l2 *= l2;

                if (l1 + l2 + _maxError < c.r * c.r)
                {
                    return true;
                }
            }

            return false;
        }

        double Solve()
        {
            vector<int> visited;
            while (visited.size() < _nodes.size())
            {
                int imin = 0;
                double dmin = _inf;
                for (size_t i = 0; i < _nodes.size(); i++)
                {
                    bool isVisited = false;
                    for (const int& v : visited)
                    {
                        if (v == i)
                        {
                            isVisited = true;
                            break;
                        }
                    }

                    if (!isVisited && (_nodes[i]._dist < dmin))
                    {
                        imin = i;
                        dmin = _nodes[i]._dist;
                    }
                }

                Node& curNode = _nodes[imin];
                for (const int neigh : curNode._neighs)
                {
                    bool isVisited = false;
                    for (const int& v : visited)
                    {
                        if (v == _nodes[neigh]._i)
                        {
                            isVisited = true;
                            break;
                        }
                    }

                    double curDist = curNode._dist + GetDist(curNode, _nodes[neigh]);
                    if (!isVisited && (curDist < _nodes[neigh]._dist))
                    {
                        _nodes[neigh]._dist = curDist;
                        _nodes[neigh]._prev = curNode._i;
                    }
                }

                visited.push_back(imin);
            }

            double dist = _nodes[_nodes.size() - 1]._dist;
            if (dist == _inf)
            {
                dist = -1;
            }

            return dist;
        }

        double GetDist(Node& n1, Node& n2) const
        {
            if ((n1._circleIndex == n2._circleIndex) && (n1._circleIndex != -1))
            {
                return 2 * _pi / _segCount * _c[n1._circleIndex].r;
            }

            double l1 = n1._x - n2._x;
            double l2 = n1._y - n2._y;
            l1 *= l1;
            l2 *= l2;
            return sqrt(l1 + l2);
        }
    };

    static double shortest_path_length(Point a, Point b, const vector<Circle>& c)
    {
        return Graph(a, b, c, segCount)._lenght;
    }

    static double GetSolution(vector<Node>& nodes)
    {
        Graph g(a, b, c, segCount);
        nodes = g._nodes;
        return g._lenght;
    }
}