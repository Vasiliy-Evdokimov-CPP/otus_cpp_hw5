#pragma once

#include "Logger.hpp"
#include "VisualTypes.hpp"

class IVisualCanvas 
{
public:
    virtual void DrawLine(Point point_1, Point point_2) = 0;
    virtual void DrawRectangle(Point left_top, Point right_bottom) = 0;
    virtual void DrawEllipse(Point left_top, Point right_bottom) = 0;
    
    void Clear()
    {
        WriteLog("Canvas has been cleared!");
    }

    Pen m_pen;
    Brush m_brush;
};

//

class DesktopCanvas: public IVisualCanvas
{
    void DrawLine(Point point_1, Point point_2) override;
    void DrawRectangle(Point left_top, Point right_bottom) override;
    void DrawEllipse(Point left_top, Point right_bottom) override;
};

void DesktopCanvas::DrawLine(Point point_1, Point point_2)
{
    WriteLog("DesktopCanvas_Draw LINE from " +
        point_1.ToString() + " to " + point_2.ToString() +
        " with pen " + m_pen.ToString()
    );
} 

void DesktopCanvas::DrawRectangle(Point left_top, Point right_bottom)
{
    WriteLog("DesktopCanvas_Draw RECTANGLE from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_pen.ToString() + 
        " and brush " + m_brush.ToString()
    );        
} 

void DesktopCanvas::DrawEllipse(Point left_top, Point right_bottom)
{
    WriteLog("DesktopCanvas_Draw ELLIPSE from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_pen.ToString() +
        " and brush " + m_brush.ToString()
    );        
} 

