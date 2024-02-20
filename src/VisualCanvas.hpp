#pragma once

#include <iostream>

#include "VisualTypes.hpp"

struct VisualCanvas 
{
public:
    void DrawLine(Point point_1, Point point_2);
    void DrawRectangle(Point left_top, Point right_bottom);
    void DrawEllipse(Point left_top, Point right_bottom);

    Pen m_pen;
    Brush m_brush;
};

void VisualCanvas::DrawLine(Point point_1, Point point_2)
{
    std::cout <<         
        "VisualCanvas: Draw LINE from " <<
        point_1.ToString() << " to " << point_2.ToString() <<
        " with pen " << m_pen.ToString()
    << std::endl;
} 

void VisualCanvas::DrawRectangle(Point left_top, Point right_bottom)
{
    std::cout << 
        "VisualCanvas: Draw RECTANGLE from " << 
        left_top.ToString() << " to " << right_bottom.ToString() << 
        " with pen " << m_pen.ToString() << 
        " and brush " << m_brush.ToString()
    << std::endl;
} 

void VisualCanvas::DrawEllipse(Point left_top, Point right_bottom)
{
    std::cout << 
        "VisualCanvas: Draw ELLIPSE from " << 
        left_top.ToString() << " to " << right_bottom.ToString() << 
        " with pen " << m_pen.ToString() <<
        " and brush " << m_brush.ToString()
    << std::endl;
} 

