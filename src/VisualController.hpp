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

    VisualObject* HitTest(Point point) 
    {
        for (int i = 0; i < m_objects.size(); ++i) 
            if (m_objects[i]->HitTest(point))
                return m_objects[i];
        return nullptr;
    }

    void HandlePoint(Point point)
    {        
        if (m_current_object_type == VisualObjectType::selector) 
        {
            m_selected_object = HitTest(point);
        } else {
            m_selected_object = nullptr;
            //
            if (m_current_object == nullptr)
                m_current_object = CreateCurrentObject(m_current_object_type);
            //
            if (m_current_object == nullptr) return;
            //
            m_current_object->AddPoint(point);
            //
            if (m_current_object->IsFinished())
            {
                m_objects.push_back(m_current_object);
                m_current_object = nullptr;
            }
        }                
    }

    void CancelPoint()
    {
        m_selected_object = nullptr;
        //
        if (m_current_object == nullptr) return;
        //
        delete m_current_object;
        m_current_object = nullptr;
    }
    
    int GetObjectsCount()
    {
        return m_objects.size();
    }

    VisualObject* GetObject(uint index)
    {
        if ((index >= 0) && (index < m_objects.size()))
            return m_objects[index];
        return nullptr;
    }

    void ClearObjects() 
    {
        for (int i = 0; i < m_objects.size(); ++i)
            delete m_objects[i];
        m_objects.clear();    
    }

        void DeleteObject(VisualObject* object)
    {
        //
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

    std::vector<VisualObject*> m_objects;

    VisualObjectType m_current_object_type = VisualObjectType::selector;
    Pen m_current_pen;
    Brush m_current_brush;

    VisualObject* m_current_object = nullptr;
    VisualObject* m_selected_object = nullptr;

};