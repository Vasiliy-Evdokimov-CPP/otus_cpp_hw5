#pragma once

#include <string>

typedef unsigned int uint;

enum class PenStyle { solid, dotted, dashed };

enum class BrushStyle { solid, clear, horizontal, vertical };

enum class Color { black, white, red, green, blue };

std::string PenStyleToString(PenStyle pen_style) 
{
    switch (pen_style) {
        case PenStyle::solid:
            return "SOLID";
        case PenStyle::dotted:
            return "DOTTED";
        case PenStyle::dashed:
            return "DASHED";                        
        default:
            return "(unknown)";    
    }
}

std::string BrushStyleToString(BrushStyle brush_style) 
{
    switch (brush_style) {
        case BrushStyle::solid:
            return "SOLID";
        case BrushStyle::clear:
            return "CLEAR";
        case BrushStyle::horizontal:
            return "HORIZONTAL"; 
        case BrushStyle::vertical:
            return "VERTICAL";                           
        default:
            return "(unknown)";    
    }
}

std::string ColorToString(Color color) 
{
    switch (color) {
        case Color::black:
            return "BLACK";
        case Color::white:
            return "WHITE";   
        case Color::red:
            return "RED";
        case Color::green: 
            return "GREEN";
        case Color::blue: 
            return "BLUE";                                             
        default:
            return "(unknown)";    
    }
}

struct Point
{
    int x;
    int y;
    
    std::string ToString() 
    {
        return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
    }
};

struct Pen 
{
    Pen(): 
        style(PenStyle::solid),
        color(Color::black),
        thickness(1) {}

    PenStyle style;
    Color color;
    unsigned int thickness;

    std::string ToString()
    {
        return "(" +
            std::to_string(thickness) + "px; " +  
            PenStyleToString(style) + "; " + 
            ColorToString(color) + 
        ")";
    }
    
};

struct Brush 
{
    Brush():
        style(BrushStyle::solid),
        color(Color::white) {}

    BrushStyle style;
    Color color;

    std::string ToString()
    {
        return "(" + 
            BrushStyleToString(style) + "; " + 
            ColorToString(color) + 
        ")";
    }
};