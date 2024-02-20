
#include <iostream>

#include "VisualTypes.hpp"

struct VisualCanvas 
{
public:
    void DrawLine(Point point_1, Point point_2);
    void DrawRectangle(Point left_top, Point right_bottom);
    void DrawEllipse(Point left_top, Point right_bottom);
private:
    Pen m_current_pen;
    Brush m_current_brush;
};

void VisualCanvas::DrawLine(Point point_1, Point point_2)
{
    std::cout << 
        "Draw LINE from " + 
        point_1.ToString() + " to " + point_2.ToString() + 
        " with pen " + m_current_pen.ToString();
} 

void VisualCanvas::DrawRectangle(Point left_top, Point right_bottom)
{
    std::cout << 
        "Draw RECT from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_current_pen.ToString() + 
        " and brush " + m_current_brush.ToString();
} 

void VisualCanvas::DrawEllipse(Point left_top, Point right_bottom)
{
    std::cout << 
        "Draw ELLIPSE from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_current_pen.ToString() + 
        " and brush " + m_current_brush.ToString();
} 

