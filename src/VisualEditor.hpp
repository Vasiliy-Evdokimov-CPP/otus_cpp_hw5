#pragma once

#include "Logger.hpp"
#include "VisualCanvas.hpp"
#include "VisualPalettes.hpp"
#include "VisualController.hpp"

class VisualEditor
{
public:
    VisualEditor(VisualController* visual_controller) 
    {
        m_controller = visual_controller;
    }

    void SelectObject(VisualObjectType object)
    {
        m_object_palette->Select(object);
    }

    void SelectPenStyle(PenStyle pen_style)
    {
        m_pen_style_palette->Select(pen_style);
    }

    void SelectBrushStyle(BrushStyle brush_style)
    {
        m_brush_style_palette->Select(brush_style);
    }

    void SelectColor(Color color)
    {
        m_color_palette->Select(color);
    }

    void SelectThickness(uint thickness)
    {
        m_thickness_selector->Select(thickness);
    }    

    void MouseDown(Point point)
    {
        WriteLog("VisualEditor MouseDown " + point.ToString());
    }

    void MouseMove(Point point) 
    {
        WriteLog("VisualEditor MouseMove " + point.ToString());
    }
    
    void MouseUp(Point point)
    {
        WriteLog("VisualEditor MouseUp " + point.ToString());
    };

protected:
    IVisualCanvas* m_canvas;
    IObjectsPalette* m_object_palette;
    IPenStylePalette* m_pen_style_palette;
    IBrushStylePalette* m_brush_style_palette;
    IColorPalette* m_color_palette;
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
        m_brush_style_palette = new DesktopBrushStylePalette();
        m_color_palette = new DesktopColorPalette();
        m_thickness_selector = new DesktopThicknessSelector();
        //
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    ~DesktopEditor() 
    {
        delete m_canvas;
        delete m_object_palette;
        delete m_pen_style_palette;
        delete m_brush_style_palette;
        delete m_color_palette;
        delete m_thickness_selector;
    }

};