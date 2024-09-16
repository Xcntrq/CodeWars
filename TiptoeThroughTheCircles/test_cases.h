#pragma once
#include "solution1.h"
#include "solution2.h"
#include "solution3.h"
#include "visualizer.h"
#include <iomanip>
#include <iostream>

static vector<Node> nodes;

static void ShowResult(double result, float scale)
{
    cout << fixed << setprecision(15) << result << (abs(result - expectation) < _maxError ? " good" : " bad") << endl;
    if (scale != 0)
    {
        cout << expectation << " needed" << endl;
        Visualizer v(nodes, scale);
    }
}

static void MyCase()
{
    a = { -3, 1 }; b = { 4.25, 0 };
    c = { {0.0, 0.0, 2.5} };
    expectation = 0.123123;
}

static void Example_In_The_Picture()
{
    a = { -3, 1 }; b = { 4.25, 0 };
    c = { {0.0, 0.0, 2.5}, {1.5, 2.0, 0.5}, {3.5, 1.0, 1.0}, {3.5, -1.7, 1.2} };
    expectation = 9.11821650244;
    ShowResult(solution1::GetSolution(nodes), 0);
    ShowResult(solution2::GetSolution(nodes), 0);
    ShowResult(solution3::GetSolution(nodes), 100);
}

static void Long_Way_Round()
{
    a = { 0, 1 }; b = { 0, -1 };
    c = { {0.0, 0.0, 0.8}, {3.8, 0.0, 3.2}, {-3.5, 0.0, 3.0}, {-7.0, 0.0, 1.0} };
    expectation = 19.0575347577;
    ShowResult(solution1::GetSolution(nodes), 0);
    ShowResult(solution2::GetSolution(nodes), 0);
    ShowResult(solution3::GetSolution(nodes), 45);
}

static void Straight_Line()
{
    a = { 3, 0 }; b = { 0, 4 };
    c = { {0, 0, 1} };
    expectation = 5;
    ShowResult(solution1::GetSolution(nodes), 0);
    ShowResult(solution2::GetSolution(nodes), 0);
    ShowResult(solution3::GetSolution(nodes), 100);
}

static void No_Way_Through()
{
    a = { 0, 0 }; b = { 20, 20 };
    c = { {4, 0, 3}, {-4, 0, 3}, {0, 4, 3}, {0, -4, 3} };
    expectation = -1;
    ShowResult(solution1::GetSolution(nodes), 0);
    ShowResult(solution2::GetSolution(nodes), 0);
    ShowResult(solution3::GetSolution(nodes), 12);
}