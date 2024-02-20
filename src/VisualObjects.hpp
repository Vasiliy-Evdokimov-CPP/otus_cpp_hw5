#include <iostream>
#include <list>

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
    
private:   
    std::list<Point> m_points;    
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
    for (int )
}

struct RectVisualObject: public FilledVisualObject
{

};

struct TSimpleLine: public LineVisualObject
{

};


struct PolyLine: public LineVisualObject
{

};

struct TRectangle: public RectVisualObject
{

};


struct Ellipse: public RectVisualObject
{

};
    
  