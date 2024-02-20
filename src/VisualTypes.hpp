#include <string>

enum class PenStyle { solid, dotted, dashed };

enum class BrushStyle { solid, clear };

enum class Color { black, white, red, green, blue };

std::string PenStyleToString(PenStyle pen_style) 
{
    switch (pen_style) {
        case PenStyle::solid:
            return "solid";
        case PenStyle::dotted:
            return "dotted";
        case PenStyle::dashed:
            return "dashed";                        
        default:
            return "(unknown)";    
    }
}

std::string BrushStyleToString(BrushStyle brush_style) 
{
    switch (brush_style) {
        case BrushStyle::solid:
            return "solid";
        case BrushStyle::clear:
            return "clear";                    
        default:
            return "(unknown)";    
    }
}

std::string ColorToString(Color color) 
{
    switch (color) {
        case Color::black:
            return "black";
        case Color::white:
            return "white";   
        case Color::red:
            return "red";
        case Color::green: 
            return "green";
        case Color::blue: 
            return "blue";                                             
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
        style(BrushStyle::clear),
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