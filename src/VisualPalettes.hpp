#pragma once

#include "Logger.hpp"
#include "VisualTypes.hpp"
#include "VisualObjects.hpp"

typedef unsigned int uint;

// template <VisualObjectType V>
// struct SelectedObject
// {
//     using type =
//         (V == VisualObjectType::simpleline)
//             ? SimpleLine
//             : ((V == VisualObjectType::polyline)
//                 ? PolyLine
//                 : ((V == VisualObjectType::rectangle)
//                     ? Rectangle
//                     : ((V == VisualObjectType::ellipse)
//                         ? Ellipse
//                         : Selector)));
// };

class IObjectsPalette 
{
private: 
    VisualObjectType m_selected; 
public:
    virtual void Draw() = 0;
    void Select(VisualObjectType object)
    {
        m_selected = object;
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
        WriteLog(ColorToString(color) + " selected");
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
        m_selected = thickness;
    }
};

class DesktopObjectsPalette: public IObjectsPalette {
    void Draw() override 
    {
        WriteLog("Draw Desktop_ObjectsPalette");
    }
};

class DesktopPenStylePalette: public IPenStylePalette {
    void Draw() override 
    {
        WriteLog("Draw Desktop_PenStylePalette");        
    }
};

class DesktopBrushStylePalette: public IBrushStylePalette {
    void Draw() override 
    {
        WriteLog("Draw Desktop_BrushStylePalette");
    }
};

class DesktopColorPalette: public IColorPalette {
    void Draw() override 
    {
        WriteLog("Draw Desktop_ColorPalette");        
    }
};

class DesktopThicknessSelector: public IThicknessSelector {
    void Draw() override 
    {
        WriteLog("Draw Desktop_ThicknessSelector");
    }
};