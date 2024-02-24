#pragma once

#include <string>

#include "Logger.hpp"
#include "VisualCanvas.hpp"
#include "VisualPalettes.hpp"
#include "VisualController.hpp"

enum class MouseButton { left, middle, right };

enum class KeyboardKey { vk_delete };

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

class VisualEditor
{
public:
    VisualEditor(std::shared_ptr<VisualController> visual_controller) 
    {
        m_controller = visual_controller;
    }

    void SelectObjectType(VisualObjectType object_type)
    {
        m_object_palette->Select(object_type);
        m_controller->SelectObjectType(object_type);
    }

    void SelectPenStyle(PenStyle pen_style)
    {
        m_pen_style_palette->Select(pen_style);
        m_controller->SetPenStyle(pen_style);
    }

    void SelectPenColor(Color color)
    {
        m_pen_color_palette->Select(color);
        m_controller->SetPenColor(color);
    }

    void SelectBrushStyle(BrushStyle brush_style)
    {
        m_brush_style_palette->Select(brush_style);
        m_controller->SetBrushStyle(brush_style);
    }

    void SelectBrushColor(Color color)
    {
        m_brush_color_palette->Select(color);
        m_controller->SetBrushColor(color);
    }

    void SelectThickness(uint thickness)
    {
        m_thickness_selector->Select(thickness);
        m_controller->SetPenThickness(thickness);
    }    

    void Redraw()
    {
        m_canvas->Clear();
        //
        for (int i = 0; i < m_controller->GetObjectsCount(); i++)
        {
            std::shared_ptr<VisualObject> obj = m_controller->GetObject(i);
            obj->Draw(m_canvas);
        }            
    }

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

    void NewFile()
    {
        m_controller->NewFile();
        m_canvas->Clear();
    }

    void SaveFile(std::string filename)
    {
        m_controller->SaveFile(filename);
    }

    void LoadFile(std::string filename)
    {        
        m_controller->LoadFile(filename);        
        Redraw();
    }

protected:
    std::shared_ptr<IVisualCanvas> m_canvas;
    std::shared_ptr<IObjectsPalette> m_object_palette;
    std::shared_ptr<IPenStylePalette> m_pen_style_palette;
    std::shared_ptr<IColorPalette> m_pen_color_palette;
    std::shared_ptr<IBrushStylePalette> m_brush_style_palette;
    std::shared_ptr<IColorPalette> m_brush_color_palette;
    std::shared_ptr<IThicknessSelector> m_thickness_selector;
    //
    std::shared_ptr<VisualController> m_controller;
};

class DesktopEditor: public VisualEditor
{    
public:
    DesktopEditor(std::shared_ptr<VisualController> visual_controller) : VisualEditor(visual_controller)
    {
        m_canvas = std::make_shared<DesktopCanvas>();
        m_object_palette = std::make_shared<DesktopObjectsPalette>();
        m_pen_style_palette = std::make_shared<DesktopPenStylePalette>();
        m_pen_color_palette = std::make_shared<DesktopColorPalette>();
        m_brush_style_palette = std::make_shared<DesktopBrushStylePalette>();
        m_brush_color_palette = std::make_shared<DesktopColorPalette>();
        m_thickness_selector = std::make_shared<DesktopThicknessSelector>();
        //
        WriteLog(__PRETTY_FUNCTION__);        
    }
    
    ~DesktopEditor() 
    {
        m_canvas = nullptr;
        m_object_palette = nullptr;
        m_pen_style_palette = nullptr;
        m_pen_color_palette = nullptr;
        m_brush_style_palette = nullptr;
        m_brush_color_palette = nullptr;
        m_thickness_selector = nullptr;
    }

};