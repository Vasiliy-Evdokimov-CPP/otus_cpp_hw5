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
    VisualEditor(VisualController* visual_controller) 
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
            VisualObject* obj = m_controller->GetObject(i);
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
        if (key == KeyboardKey::vk_delete)
        {
            //
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
    IVisualCanvas* m_canvas;
    IObjectsPalette* m_object_palette;
    IPenStylePalette* m_pen_style_palette;
    IColorPalette* m_pen_color_palette;
    IBrushStylePalette* m_brush_style_palette;
    IColorPalette* m_brush_color_palette;
    IThicknessSelector* m_thickness_selector;
    //
    VisualController* m_controller;
};

class DesktopEditor: public VisualEditor
{    
public:
    DesktopEditor(VisualController* visual_controller) : VisualEditor(visual_controller)
    {
        m_canvas = new DesktopCanvas();
        m_object_palette = new DesktopObjectsPalette();
        m_pen_style_palette = new DesktopPenStylePalette();
        m_pen_color_palette = new DesktopColorPalette();
        m_brush_style_palette = new DesktopBrushStylePalette();
        m_brush_color_palette = new DesktopColorPalette();
        m_thickness_selector = new DesktopThicknessSelector();
        //
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    ~DesktopEditor() 
    {
        delete m_canvas;
        delete m_object_palette;
        delete m_pen_style_palette;
        delete m_pen_color_palette;
        delete m_brush_style_palette;
        delete m_brush_color_palette;
        delete m_thickness_selector;
    }

};