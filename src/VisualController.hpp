#pragma once

#include <vector>

#include "Logger.hpp"
#include "VisualTypes.hpp"
#include "VisualObjects.hpp"

class VisualController 
{
public:
    VisualController()
    {
        WriteLog("VisualController()");
        ClearObjects();
    }

    ~VisualController()
    {
        WriteLog("~VisualController()");
        ClearObjects();
    }

    void SelectObjectType(VisualObjectType object_type)
    {
        m_current_object_type = object_type;
    }

    void SetPenStyle(PenStyle pen_style)
    {
        m_current_pen.style = pen_style;
    }
    void SetPenColor(Color color)
    {
        m_current_pen.color = color;
    }
    void SetPenThickness(uint thickness)
    {
        m_current_pen.thickness = thickness;
    }

    void SetBrushStyle(BrushStyle brush_style)
    {
        m_current_brush.style = brush_style;
    }
    void SetBrushColor(Color color)
    {
        m_current_brush.color = color;
    }

    void AddPoint(Point point)
    {        
        if (m_current_object == nullptr)
        {
            m_current_object = CreateCurrentObject(m_current_object_type);
        }
        //
        if (m_current_object == nullptr) return;
        //
        m_current_object->AddPoint(point);
        //
        if (m_current_object->IsFinished())
        {
            objects.push_back(m_current_object);
            m_current_object = nullptr;
        }        
    }

    void DeleteLastPoint()
    {
        if (m_current_object == nullptr) return;
        //
        delete m_current_object;
        m_current_object = nullptr;
    }
    
    int GetObjectsCount()
    {
        return objects.size();
    }

    VisualObject* GetObject(uint index)
    {
        if ((index >= 0) && (index < objects.size()))
            return objects[index];
        return nullptr;
    }

    void ClearObjects() 
    {
        for (int i = 0; i < objects.size(); ++i)
            delete objects[i];
        objects.clear();    
    }

    void NewFile()
    {
        ClearObjects();
    };

    void LoadFile(std::string filename)
    {
        //
    };

    void SaveFile(std::string filename)
    {
        //
    };

private:
    VisualObject* CreateCurrentObject(VisualObjectType object_type) 
    {
        switch (object_type)
        {
            case VisualObjectType::line :
                return new SimpleLine(m_current_pen);
                break;
            case VisualObjectType::rectangle :
                return new Rectangle(m_current_pen, m_current_brush);
                break;
            case VisualObjectType::ellipse :
                return new Ellipse(m_current_pen, m_current_brush);
                break;
            default:
                return nullptr;
                break;
        }
    }

    std::vector<VisualObject*> objects;

    VisualObjectType m_current_object_type = VisualObjectType::selector;
    Pen m_current_pen;
    Brush m_current_brush;

    VisualObject* m_current_object = nullptr;
};