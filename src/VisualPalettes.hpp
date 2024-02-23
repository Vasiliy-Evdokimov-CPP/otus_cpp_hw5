#pragma once

#include <string>

#include "Logger.hpp"
#include "VisualTypes.hpp"
#include "VisualObjects.hpp"

class IObjectsPalette 
{
private: 
    VisualObjectType m_selected; 
public:
    virtual void Draw() = 0;
    void Select(VisualObjectType object_type)
    {
        WriteLog(ObjectTypeToString(object_type) + " object selected");
        m_selected = object_type;
    }
};

class IPenStylePalette
{
private: 
    PenStyle m_selected;
public:
    virtual void Draw() = 0;
    void Select(PenStyle pen_style)
    {
        WriteLog(PenStyleToString(pen_style) + " pen selected");
        m_selected = pen_style;
    }
};

class IBrushStylePalette
{
private: 
    BrushStyle m_selected;
public:
    virtual void Draw() = 0;
    void Select(BrushStyle brush_style)
    {
        WriteLog(BrushStyleToString(brush_style) + " brush selected");
        m_selected = brush_style;
    }
};

class IColorPalette
{
private: 
    Color m_selected;
public:
    virtual void Draw() = 0;
    void Select(Color color)
    {
        m_selected = color;
        WriteLog(ColorToString(color) + " color selected");
    }
};

class IThicknessSelector
{
private: 
    uint m_selected;
public:
    virtual void Draw() = 0;
    void Select(uint thickness)
    {
        WriteLog(std::to_string(thickness) + "px thickness selected");
        m_selected = thickness;
    }
};

class DesktopObjectsPalette: public IObjectsPalette
{
    void Draw() override 
    {
        WriteLog("Draw Desktop_ObjectsPalette");
    }
};

class DesktopPenStylePalette: public IPenStylePalette
{
    void Draw() override 
    {
        WriteLog("Draw Desktop_PenStylePalette");        
    }
};

class DesktopBrushStylePalette: public IBrushStylePalette
{
    void Draw() override 
    {
        WriteLog("Draw Desktop_BrushStylePalette");
    }
};

class DesktopColorPalette: public IColorPalette
{
    void Draw() override 
    {
        WriteLog("Draw Desktop_ColorPalette");        
    }
};

class DesktopThicknessSelector: public IThicknessSelector
{
    void Draw() override 
    {
        WriteLog("Draw Desktop_ThicknessSelector");
    }
};