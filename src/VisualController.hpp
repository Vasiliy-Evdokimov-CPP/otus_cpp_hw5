#pragma once

/**
    \file
    \details
        В файле описывается класс визуального контроллера
*/

#include <memory>

#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Logger.hpp"
#include "VisualTypes.hpp"
#include "VisualObjects.hpp"

/**
    \brief
        Визуальный контроллер
    \details
        Отвечает за создание, хранение объектов
*/
class VisualController 
{
public:
    /**
        \brief
            Конструктор контроллера
    */
    VisualController()
    {
        WriteLog("VisualController()");
        ClearObjects();
    }
    /**
        \brief
            Деструктор контроллера
    */
    ~VisualController()
    {
        WriteLog("~VisualController()");
        ClearObjects();
    }
    /**
        \brief
            Метод задания текущего создавемого объекта
        \param object_type тип объекта
    */
    void SelectObjectType(VisualObjectType object_type)
    {
        m_current_object_type = object_type;
    }
    /**
        \brief
            Метод задания текущего стиля пера
        \param pen_style стиль пера
    */
    void SetPenStyle(PenStyle pen_style)
    {
        m_current_pen.style = pen_style;
    }
    /**
        \brief
            Метод задания текущего цвета пера
        \param color цвет пера
    */
    void SetPenColor(Color color)
    {
        m_current_pen.color = color;
    }
    /**
        \brief
            Метод задания текущей толщины пера
        \param thickness толщина пера
    */
    void SetPenThickness(uint thickness)
    {
        m_current_pen.thickness = thickness;
    }
    /**
        \brief
            Метод задания текущего стиля кисти
        \param brush_style стиль кисти
    */
    void SetBrushStyle(BrushStyle brush_style)
    {
        m_current_brush.style = brush_style;
    }
    /**
        \brief
            Метод задания текущего цвета кисти
        \param brush_style цвет кисти
    */
    void SetBrushColor(Color color)
    {
        m_current_brush.color = color;
    }
    /**
        \brief
            Поиск объекта, содержащего внутри указанную точку
        \param point точка для проверки
    */      
    std::shared_ptr<VisualObject> HitTest(Point point) 
    {
        for (size_t i = 0; i < m_objects.size(); ++i) 
            if (m_objects[i]->HitTest(point))
                return m_objects[i];
        return nullptr;
    }
    /**
        \brief
            Обработка контроллером новой точки
        \details
            Создание нового объекта, выбор существующего объекьа, создание новой точки в конструируемом объекте
        \param point новая точка
    */ 
    void HandlePoint(Point point)
    {        
        if (m_current_object_type == VisualObjectType::selector) 
        {
            m_selected_object = HitTest(point);
            //
            if (m_selected_object != nullptr)
                WriteLog("(" + m_selected_object->Serialize() + ") has been selected!");
        } else {
            m_selected_object = nullptr;
            //
            if (m_current_object == nullptr)
                m_current_object = CreateObject(m_current_object_type);
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
    /**
        \brief
            Обработка отмены конструирования
    */ 
    void CancelPoint()
    {
        m_selected_object = nullptr;
        m_current_object = nullptr;
    }
    /**
        \brief
            Получение количества объектов
    */ 
    int GetObjectsCount()
    {
        return m_objects.size();
    }
    /**
        \brief
            Получение объекта по индексу
    */
    std::shared_ptr<VisualObject> GetObject(uint index)
    {
        if (index < m_objects.size())
            return m_objects[index];
        return nullptr;
    }
    /**
        \brief
            Удаление всех объектов
    */
    void ClearObjects() 
    {
        for (size_t i = 0; i < m_objects.size(); ++i)
            m_objects[i] = nullptr;
        m_objects.clear();    
    }
    /**
        \brief
            Удаление объекта
    */
    int DeleteObject(std::shared_ptr<VisualObject> object)
    {
        if (object == nullptr) return 0;
        //
        auto found = std::find_if(m_objects.begin(), m_objects.end(), 
            [&](const std::shared_ptr<VisualObject>& ptr) { return ptr == object; });
        //
        if (found == m_objects.end()) return 0;
        //
        m_objects.erase(found); 
        return 1;            
    }
    /**
        \brief
            Создание нового файла
    */
    void NewFile()
    {
        ClearObjects();
    };
    /**
        \brief
           Загрузка файла
        \param point имя файла
    */ 
    void LoadFile(std::string filename)
    {
        ClearObjects();
        //
        std::ifstream in(filename);
        if (in.is_open())
        {
            std::string line, s_type; 
            int points_count, x, y;           
            //
            while (std::getline(in, line))
            {
                std::stringstream ss(line);
                ss >> s_type;                
                //
                auto vo_type = StringToObjectType(s_type);
                if (vo_type != VisualObjectType::unknown)
                {                    
                    auto new_object = CreateObject(vo_type);                    
                    ss >> points_count;
                    for (int i = 0; i < points_count; ++i)
                    {
                        ss >> x >> y;
                        new_object->AddPoint(Point{x, y});
                    }
                    m_objects.push_back(new_object);
                } 
            }
        }
        in.close();
        //
        WriteLog("File \"" + filename + "\" has been loaded!");
    };
    /**
        \brief
           Сохранение файла
        \param point имя файла
    */ 
    void SaveFile(std::string filename)
    {
        std::ofstream out;
        out.open(filename);
        if (out.is_open())
        {
            for (size_t i = 0; i < m_objects.size(); ++i)
                out << m_objects[i]->Serialize() << std::endl;
        }                
        out.close();
        //
        WriteLog("File \"" + filename + "\" has been saved!");
    };
    /**
        \brief
           Удаление текущего выбранного объекта
    */
    void DeleteSelectedObject() 
    { 
        if (DeleteObject(m_selected_object)) {
            m_selected_object = nullptr;
        }
    }

private:
    /**
        \brief
           Создание объекта указанного типа
        \param object_type тип объекта
    */ 
    std::shared_ptr<VisualObject> CreateObject(VisualObjectType object_type) 
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
    /**
        \brief
            Список объектов
    */
    std::vector<std::shared_ptr<VisualObject>> m_objects;
    /**
        \brief
            Текущий выбранный тип объекта
    */
    VisualObjectType m_current_object_type = VisualObjectType::selector;
    /**
        \brief
            Текущее перо
    */
    Pen m_current_pen;
    /**
        \brief
            Текущая кисть
    */
    Brush m_current_brush;
    /**
        \brief
            Конструируемый объект
    */
    std::shared_ptr<VisualObject> m_current_object;
    /**
        \brief
            Выбранный объект
    */
    std::shared_ptr<VisualObject> m_selected_object;

};