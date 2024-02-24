#pragma once

#include <vector>
#include <map>

#include "VisualTypes.hpp"
#include "VisualCanvas.hpp"

const int HIT_TOLERANCE = 3;

enum class VisualObjectType { unknown, selector, line, rectangle, ellipse };

std::map<VisualObjectType, std::string> ObjectTypeToStringMap = 
{
    { VisualObjectType::unknown,    "(unknown)" }, 
    { VisualObjectType::selector,   "SELECTOR" }, 
    { VisualObjectType::line,       "LINE" }, 
    { VisualObjectType::rectangle,  "RECTANGLE" }, 
    { VisualObjectType::ellipse,    "ELLIPSE" }
};

std::string ObjectTypeToString(VisualObjectType object_type)
{
    if (ObjectTypeToStringMap.count(object_type) == 0)
        return ObjectTypeToStringMap[VisualObjectType::unknown];
    //
    return ObjectTypeToStringMap[object_type];     
}

VisualObjectType StringToObjectType(std::string object_type)
{
    for(auto iter{ObjectTypeToStringMap.begin()}; iter != ObjectTypeToStringMap.end(); iter++)
        if (iter->second == object_type) 
            return iter->first;
    //        
    return VisualObjectType::unknown;
}

class BaseVisualObject {};

class Selector: public BaseVisualObject {};

class VisualObject: public BaseVisualObject
{
public:
    VisualObject()
    {        
        WriteLog("VisualObject()");
    }
    ~VisualObject()
    {        
        WriteLog("~VisualObject()");
        //
        m_points.clear();
    }    
    size_t GetPointsCount()
    {
        return m_points.size();
    }    
    size_t GetMaxPointsCount()
    {
        return m_max_points_count;
    }  
    virtual void AddPoint(Point point)  
    {
        m_points.push_back(point);
    }
    int IsFinished() 
    {
        return (m_points.size() == GetMaxPointsCount());
    }

    virtual std::string Serialize()
    {
        std::string res = ObjectTypeToString(m_type);
        //
        res += " " + std::to_string(m_points.size());
        //
        for (size_t i = 0; i < m_points.size(); ++i)
            res += " " + m_points[i].Serialize();
        //
        return res;    
    }

    virtual std::string GetTypeName()
    {
        return ObjectTypeToString(m_type);
    }

    virtual void Draw(std::shared_ptr<IVisualCanvas> canvas) = 0;
    virtual int HitTest(Point point) = 0;
    
    Pen m_pen;
    
protected:
    size_t m_max_points_count = 2;
    std::vector<Point> m_points;
    VisualObjectType m_type = VisualObjectType::unknown;
       
};

class FilledVisualObject: public VisualObject
{   
public:
    Brush m_brush;
};

class LineVisualObject: public VisualObject
{
public:
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        canvas->m_pen = m_pen;    
        //
        for (size_t i = 1; i < m_points.size(); ++i)
            canvas->DrawLine(m_points[i - 1], m_points[i]);
    }
    int HitTest(Point point) override 
    {
        if (m_points.size() < 2) return 0;
        //
        return distance(point, m_points[0], m_points[1]) < HIT_TOLERANCE;
    }
};

class RectVisualObject: public FilledVisualObject
{
public:
    int HitTest(Point point) 
    {
        if (m_points.size() < 2) return 0;
        //
        return 
            ((point.x > m_points[0].x - HIT_TOLERANCE) && (point.x < m_points[1].x + HIT_TOLERANCE) &&
             (point.y > m_points[0].y - HIT_TOLERANCE) && (point.y < m_points[1].y + HIT_TOLERANCE));        
    }
    RectVisualObject(Pen pen, Brush brush)
    {
        m_pen = pen;
        m_brush = brush;
    } 
    virtual void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        canvas->m_pen = m_pen;    
        canvas->m_brush = m_brush;    
    }
};

class SimpleLine: public LineVisualObject
{
public:
    SimpleLine()
    {    
        WriteLog("SimpleLine()");
        //
        m_max_points_count = 2;
        m_type = VisualObjectType::line;
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
        WriteLog("Rectangle()");
        //
        m_type = VisualObjectType::rectangle;
    };
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        RectVisualObject::Draw(canvas);
        //
        canvas->DrawRectangle(m_points[0], m_points[1]);
    }
};

class Ellipse: public RectVisualObject
{
public:
    Ellipse(Pen pen, Brush brush) : RectVisualObject(pen, brush) 
    {
        WriteLog("Ellipse()");
        //
        m_type = VisualObjectType::ellipse;
    };
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        RectVisualObject::Draw(canvas);
        //
        canvas->DrawEllipse(m_points[0], m_points[1]);
    }
}; 