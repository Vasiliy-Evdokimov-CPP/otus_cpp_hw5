#pragma once

#include <vector>

#include "VisualTypes.hpp"
#include "VisualCanvas.hpp"

enum class VisualObjectType { selector, line, rectangle, ellipse };

std::string ObjectTypeToString(VisualObjectType object_type)
{
    switch (object_type) 
    {
        case VisualObjectType::line:
            return "LINE";
        case VisualObjectType::rectangle:
            return "RECTANGLE";
        case VisualObjectType::ellipse:
            return "ELLIPSE";   
        default:
            return "(unknown)";     
    }
}

class BaseVisualObject {};

class Selector: public BaseVisualObject {};

class VisualObject: public BaseVisualObject
{
public:
    VisualObject()
    {        
        WriteLog("VisualObject()");
        //
        m_is_selected = 0; 
    }

    ~VisualObject()
    {        
        WriteLog("~VisualObject()");
        //
        m_points.clear();
    }

    virtual void Draw(IVisualCanvas* canvas) = 0;
    int GetPointsCount()
    {
        return m_points.size();
    }    
    int GetMaxPointsCount()
    {
        return m_max_points_count;
    }  
    virtual void AddPoint(Point point)  
    {
        m_points.push_back(point);
    }
    int IsFinished() 
    {
        return (GetMaxPointsCount() == 0) || (m_points.size() == GetMaxPointsCount());
    }

    Pen m_pen;
    
protected:
    int m_max_points_count = 2;
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
    void Draw(IVisualCanvas* canvas) override;
};

void LineVisualObject::Draw(IVisualCanvas* canvas)
{
    canvas->m_pen = m_pen;    
    //
    for (int i = 1; i < m_points.size(); ++i)
        canvas->DrawLine(m_points[i - 1], m_points[i]);
}

class RectVisualObject: public FilledVisualObject
{
public:
    RectVisualObject(Pen pen, Brush brush)
    {
        m_pen = pen;
        m_brush = brush;
    } 
    virtual void Draw(IVisualCanvas* canvas) override;
};

void RectVisualObject::Draw(IVisualCanvas* canvas)
{
    canvas->m_pen = m_pen;    
    canvas->m_brush = m_brush;    
}

class SimpleLine: public LineVisualObject
{
public:
    SimpleLine()
    {    
        WriteLog("SimpleLine()");
        //
        m_max_points_count = 2;
    } 
    SimpleLine(Pen pen) : SimpleLine()
    {
        m_pen = pen;
    }    
};

class Rectangle: public RectVisualObject
{
public:
    Rectangle(Pen pen, Brush brush) : RectVisualObject(pen, brush) 
    {
        //
    };
    void Draw(IVisualCanvas* canvas) override;
};

void Rectangle::Draw(IVisualCanvas* canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas->DrawRectangle(m_points[0], m_points[1]);
}

class Ellipse: public RectVisualObject
{
public:
    Ellipse(Pen pen, Brush brush) : RectVisualObject(pen, brush) 
    {
        //
    };
    void Draw(IVisualCanvas* canvas) override;
};

void Ellipse::Draw(IVisualCanvas* canvas) 
{
    RectVisualObject::Draw(canvas);
    //
    canvas->DrawEllipse(m_points[0], m_points[1]);
}
    
  