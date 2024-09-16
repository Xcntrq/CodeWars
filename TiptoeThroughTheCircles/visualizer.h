#pragma once
#include "globals.h"
#include "node.h"
#include <SFML/Graphics.hpp>

using namespace sf;

struct Visualizer
{
    vector<Node>& _nodes;

    float _scale;
    unique_ptr<RenderWindow> _window;

    Visualizer(vector<Node>& nodes, float scale) : _nodes(nodes), _scale(scale), _window(make_unique<RenderWindow>(VideoMode(windowWidth, windowHeight), "Window"))
    {
        if (_window->isOpen())
        {
            _window->clear(Color::White);

            DrawCircles(Color::Yellow);
            DrawConnections(Color::Green);
            DrawNodes(Color::Red);
            DrawPath(Color::Black);

            _window->display();
        }

        while (_window->isOpen())
        {
            Event event;
            while (_window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    _window->close();

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                    _window->close();
            }
        }
    }

    void DrawCircles(Color color) const
    {
        for (const Circle& circle : c)
        {
            float r = (float)circle.r * _scale;
            float x = (float)windowWidth * 0.5f + _scale * (float)circle.ctr.x - r;
            float y = (float)windowHeight * 0.5f - _scale * (float)circle.ctr.y - r;
            CircleShape shape(r, 50U);
            shape.setFillColor(color);
            shape.setPosition(x, y);
            _window->draw(shape);
        }
    }

    void DrawConnections(Color color) const
    {
        vector<int> visited;
        for (Node& node : _nodes)
        {
            for (const int i : node._neighs)
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

                if (!isVisited)
                {
                    DrawLine(node, _nodes[i], color);
                }
            }
        }
    }

    void DrawNodes(Color color)
    {
        for (Node& node : _nodes)
        {
            DrawPoint(node, color, 2);
        }
    }

    void DrawPath(Color color)
    {
        int i = _nodes.size() - 1;
        while ((i != 0) && (_nodes[i]._prev != -1))
        {
            DrawLine(_nodes[i], _nodes[_nodes[i]._prev], color);
            DrawPoint(_nodes[_nodes[i]._prev], color, 3);
            DrawPoint(_nodes[i], color, 3);
            i = _nodes[i]._prev;
        }
    }

    void DrawLine(Node& n1, Node& n2, Color c) const
    {
        Vertex line[] =
        {
            Vertex(Vector2f((float)windowWidth * 0.5f + _scale * (float)n1._x, (float)windowHeight * 0.5f - _scale * (float)n1._y)),
            Vertex(Vector2f((float)windowWidth * 0.5f + _scale * (float)n2._x, (float)windowHeight * 0.5f - _scale * (float)n2._y)),
        };

        line[0].color = c;
        line[1].color = c;
        _window->draw(line, 2, Lines);
    }

    void DrawPoint(Node& n, Color c, float r) const
    {
        float x = (float)windowWidth * 0.5f + _scale * (float)n._x - r;
        float y = (float)windowHeight * 0.5f - _scale * (float)n._y - r;
        CircleShape shape(r, 10U);
        shape.setFillColor(c);
        shape.setPosition(x, y);
        _window->draw(shape);
    }
};