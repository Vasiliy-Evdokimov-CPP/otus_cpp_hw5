#pragma once

#include <memory>
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

    std::shared_ptr<VisualObject> HitTest(Point point) 
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
        m_current_object = nullptr;
    }
    
    int GetObjectsCount()
    {
        return m_objects.size();
    }

    std::shared_ptr<VisualObject> GetObject(uint index)
    {
        if ((index >= 0) && (index < m_objects.size()))
            return m_objects[index];
        return nullptr;
    }

    void ClearObjects() 
    {
        for (int i = 0; i < m_objects.size(); ++i)
            m_objects[i] = nullptr;
        m_objects.clear();    
    }

    void DeleteObject(std::shared_ptr<VisualObject> object)
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
    std::shared_ptr<VisualObject> CreateCurrentObject(VisualObjectType object_type) 
    {
        switch (object_type)
        {
            case VisualObjectType::line :
                return std::make_shared<SimpleLine>(m_current_pen);
                break;
            case VisualObjectType::rectangle :
                return std::make_shared<Rectangle>(m_current_pen, m_current_brush);
                break;
            case VisualObjectType::ellipse :
                return std::make_shared<Ellipse>(m_current_pen, m_current_brush);
                break;
            default:
                return nullptr;
                break;
        }
    }

    std::vector<std::shared_ptr<VisualObject>> m_objects;

    VisualObjectType m_current_object_type = VisualObjectType::selector;
    Pen m_current_pen;
    Brush m_current_brush;

    std::shared_ptr<VisualObject> m_current_object;
    std::shared_ptr<VisualObject> m_selected_object;

};