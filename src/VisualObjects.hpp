#pragma once

#include <iostream>
#include <vector>

#include "VisualTypes.hpp"
#include "VisualCanvas.hpp"

struct VisualObject 
{
public:
    VisualObject()
    {        
        m_is_selected = 0; 
        m_points.clear();       
    }
    virtual void Draw(VisualCanvas canvas) = 0;
    virtual void AddPoint(Point point) = 0;

    Pen m_pen;
    
protected:   
    std::vector<Point> m_points;    
    int m_is_selected;
};

struct FilledVisualObject: public VisualObject
{   
public:
    Brush m_brush;
};

struct LineVisualObject: public VisualObject
{
public:
    void Draw(VisualCanvas canvas) override;
};

void LineVisualObject::Draw(VisualCanvas canvas)
{
    canvas.m_pen = m_pen;    
    //
    for (int i = 1; i < m_points.size(); ++i)
        canvas.DrawLine(m_points[i - 1], m_points[i]);
}

struct RectVisualObject: public FilledVisualObject
{
public:
    void Draw(VisualCanvas canvas) override;
};

void RectVisualObject::Draw(VisualCanvas canvas)
{
    canvas.m_pen = m_pen;    
    canvas.m_brush = m_brush;    
}

struct SimpleLine: public LineVisualObject
{
    //  { only two points }
};


struct PolyLine: public LineVisualObject
{
    // { delete last point on right click }
};

struct Rectangle: public RectVisualObject
{
public:
    void Draw(VisualCanvas canvas) override;
};

void Rectangle::Draw(VisualCanvas canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas.DrawRectangle(m_points[0], m_points[1]);
}

struct Ellipse: public RectVisualObject
{
public:
    void Draw(VisualCanvas canvas) override;
};

void Ellipse::Draw(VisualCanvas canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas.DrawEllipse(m_points[0], m_points[1]);
}
    
  