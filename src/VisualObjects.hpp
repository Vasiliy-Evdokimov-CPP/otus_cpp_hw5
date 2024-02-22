#pragma once

#include <vector>

#include "VisualTypes.hpp"
#include "VisualCanvas.hpp"

enum class VisualObjectType { selector, simpleline, polyline, rectangle, ellipse };

class BaseVisualObject {};

class Selector: public BaseVisualObject {};

class VisualObject: public BaseVisualObject
{
public:
    VisualObject()
    {        
        m_is_selected = 0; 
        m_points.clear();       
    }
    virtual void Draw(IVisualCanvas& canvas) = 0;
    virtual void AddPoint(Point point)  
    {
        m_points.push_back(point);
    }

    Pen m_pen;
    
protected:   
    std::vector<Point> m_points;    
    int m_is_selected;
};

class FilledVisualObject: public VisualObject
{   
public:
    Brush m_brush;
};

class LineVisualObject: public VisualObject
{
public:
    void Draw(IVisualCanvas& canvas) override;
};

void LineVisualObject::Draw(IVisualCanvas& canvas)
{
    canvas.m_pen = m_pen;    
    //
    for (int i = 1; i < m_points.size(); ++i)
        canvas.DrawLine(m_points[i - 1], m_points[i]);
}

class RectVisualObject: public FilledVisualObject
{
public:
    void Draw(IVisualCanvas& canvas) override;
};

void RectVisualObject::Draw(IVisualCanvas& canvas)
{
    canvas.m_pen = m_pen;    
    canvas.m_brush = m_brush;    
}

class SimpleLine: public LineVisualObject
{
    //  { only two points }
};


class PolyLine: public LineVisualObject
{
    // { delete last point on right click }
};

class Rectangle: public RectVisualObject
{
public:
    void Draw(IVisualCanvas& canvas) override;
};

void Rectangle::Draw(IVisualCanvas& canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas.DrawRectangle(m_points[0], m_points[1]);
}

class Ellipse: public RectVisualObject
{
public:
    void Draw(IVisualCanvas& canvas) override;
};

void Ellipse::Draw(IVisualCanvas& canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas.DrawEllipse(m_points[0], m_points[1]);
}
    
  