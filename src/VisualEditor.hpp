#pragma once

/**
    \file
    \details
        В файле описывается класс визуального редактора и реализация его потомка - desktop редактора
*/

#include <string>

#include "Logger.hpp"
#include "VisualCanvas.hpp"
#include "VisualController.hpp"

/**
    \details
        Кнопки мыши
*/
enum class MouseButton { left, middle, right };

/**
    \details
        Клавиши клавиатуры
*/
enum class KeyboardKey { vk_delete };

/**
    \brief
        Преобразование кнопок мыши в строку
    \param mouse_button кнопка мыши
*/
std::string MouseButtonToString(MouseButton mouse_button) 
{
    switch (mouse_button) 
    {
        case MouseButton::left:
            return "[LEFT_BTN]";
        case MouseButton::right:
            return "[RIGHT_BTN]";                        
        default:
            return "(unknown)";    
    }
}

/**
    \brief
        Преобразование клавиш клавиатуры в строку
    \param keyboard_key клавиша клавиатуры
*/
std::string KeyboardKeyToString(KeyboardKey keyboard_key) 
{
    switch (keyboard_key) 
    {
        case KeyboardKey::vk_delete:
            return "[VK_DELETE]";                    
        default:
            return "(unknown)";    
    }
}

/**
    \brief
        Визуальный редактор
    \details
        Позволяет редактировать векторное изображение.
        Может быть в разных реализациях - desktop, web, mobile...
*/
class VisualEditor
{
public:
    /**
        \brief
            Конструктор
        \param visual_controller контрроллер
    */
    VisualEditor(std::shared_ptr<VisualController> visual_controller) 
    {
        m_controller = visual_controller;
    }

    /**
        \brief
            Выбор типа создаваемого объекта
        \param object_type тип объекта
    */
    void SelectObjectType(VisualObjectType object_type)
    {
        m_controller->SelectObjectType(object_type);
    }

    /**
        \brief
            Выбор типа пера
        \param pen_style тип пера
    */
    void SelectPenStyle(PenStyle pen_style)
    {
        m_controller->SetPenStyle(pen_style);
    }

    /**
        \brief
            Выбор цвета пера
        \param color цвет пера
    */
    void SelectPenColor(Color color)
    {
        m_controller->SetPenColor(color);
    }

    /**
        \brief
            Выбор типа кисти
        \param brush_style тип кисти
    */
    void SelectBrushStyle(BrushStyle brush_style)
    {
        m_controller->SetBrushStyle(brush_style);
    }

    /**
        \brief
            Выбор цвета кисти
        \param color цвет кисти
    */
    void SelectBrushColor(Color color)
    {
        m_controller->SetBrushColor(color);
    }

    /**
        \brief
            Выбор толщины пера
        \param thickness толщина пера
    */
    void SelectThickness(uint thickness)
    {
        m_controller->SetPenThickness(thickness);
    }    

    /**
        \brief
            Перерисовка редактора
    */
    void Redraw()
    {
        m_canvas->Clear();
        //
        for (size_t i = 0; i < m_controller->GetObjectsCount(); i++)
        {
            std::shared_ptr<VisualObject> obj = m_controller->GetObject(i);
            obj->Draw(m_canvas);
        }            
    }

    /**
        \brief
            Нажатие кнопки мыши 
        \param point позиция курсора
        \param button кнопка мыши
    */
    void MouseDown(Point point, MouseButton button)
    {
        WriteLog("MouseDown " + MouseButtonToString(button) + " at " + point.ToString());
        //
        if (button == MouseButton::left)
            m_controller->HandlePoint(point);
        if (button == MouseButton::right)
            m_controller->CancelPoint();   
        //
        Redraw();
    }

    /**
        \brief
            Нажатие клавиши клавиатуры 
        \param key клавиша
    */
    void KeyPress(KeyboardKey key)
    {
        WriteLog("KeyboardKeyDown " + KeyboardKeyToString(key));
        //
        if (key == KeyboardKey::vk_delete)
        {
            m_controller->DeleteSelectedObject();
            Redraw();
        }
    }

    /**
        \brief
            Создание файла
    */
    void NewFile()
    {
        m_controller->NewFile();
        m_canvas->Clear();
    }

    /**
        \brief
            Сохранение файла 
        \param filename имя файла
    */
    void SaveFile(std::string filename)
    {
        m_controller->SaveFile(filename);
    }

    /**
        \brief
            Загрузка файла 
        \param filename имя файла
    */
    void LoadFile(std::string filename)
    {        
        m_controller->LoadFile(filename);        
        Redraw();
    }

protected:
    /**
        \brief
            Холст редактора 
    */
    std::shared_ptr<IVisualCanvas> m_canvas;

    /**
        \brief
            Контроллер
    */
    std::shared_ptr<VisualController> m_controller;
};


/**
    \brief
        Визуальный desktop редактор
    \details
        Состоит из соответствующих desktop компонентов
*/
class DesktopEditor: public VisualEditor
{    
public:
    /**
        \brief
            Конструктор
    */   
    DesktopEditor(std::shared_ptr<VisualController> visual_controller) : VisualEditor(visual_controller)
    {
        WriteLog("DesktopEditor()");
        //
        m_canvas = std::make_shared<DesktopCanvas>();
    }
    
    /**
        \brief
            Деструктор
    */
    ~DesktopEditor() 
    {
        m_canvas = nullptr;
    }

};