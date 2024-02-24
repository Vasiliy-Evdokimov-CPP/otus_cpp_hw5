#pragma once

#include <string>
#include <cmath>
#include <map>

typedef unsigned int uint;

enum class PenStyle { unknown, solid, dotted, dashed };

enum class BrushStyle { unknown, solid, clear, horizontal, vertical };

enum class Color { unknown, black, white, red, green, blue };

std::map<PenStyle, std::string> PenStyleToStringMap = 
{
    { PenStyle::unknown,    "(unknown)" }, 
    { PenStyle::solid,      "SOLID" }, 
    { PenStyle::dotted,     "DOTTED" }, 
    { PenStyle::dashed,     "DASHED" }
};

std::map<BrushStyle, std::string> BrushStyleToStringMap = 
{
    { BrushStyle::unknown,      "(unknown)" }, 
    { BrushStyle::solid,        "SOLID" }, 
    { BrushStyle::clear,        "CLEAR" }, 
    { BrushStyle::horizontal,   "HORIZONTAL" },
    { BrushStyle::vertical,     "VERTICAL" }
};

std::map<Color, std::string> ColorToStringMap = 
{
    { Color::unknown,   "(unknown)" }, 
    { Color::black,     "BLACK" }, 
    { Color::white,     "WHITE" }, 
    { Color::red,       "RED" },
    { Color::green,     "GREEN" },
    { Color::blue,      "BLUE" }
};

std::string PenStyleToString(PenStyle pen_style) 
{
    if (PenStyleToStringMap.count(pen_style) == 0)
        return PenStyleToStringMap[PenStyle::unknown];
    //
    return PenStyleToStringMap[pen_style];     
}

std::string BrushStyleToString(BrushStyle brush_style) 
{
    if (BrushStyleToStringMap.count(brush_style) == 0)
        return BrushStyleToStringMap[BrushStyle::unknown];
    //
    return BrushStyleToStringMap[brush_style];    
}

std::string ColorToString(Color color) 
{
    if (ColorToStringMap.count(color) == 0)
        return ColorToStringMap[Color::unknown];
    //
    return ColorToStringMap[color]; 
}

struct Point
{
    int x;
    int y;
    
    std::string ToString() 
    {
        return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
    }

    std::string Serialize() 
    {
        return std::to_string(x) + " " + std::to_string(y);
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

double distance(Point p, Point p1, Point p2) 
{
    double A = p.x - p1.x;
    double B = p.y - p1.y;
    double C = p2.x - p1.x;
    double D = p2.y - p1.y;
    
    double dot = A * C + B * D;
    double len_sq = C * C + D * D;
    double param = dot / len_sq;
    
    double xx, yy;
    if (param < 0) {
        xx = p1.x;
        yy = p1.y;
    }
    else if (param > 1) {
        xx = p2.x;
        yy = p2.y;
    }
    else {
        xx = p1.x + param * C;
        yy = p1.y + param * D;
    }
    
    double dx = p.x - xx;
    double dy = p.y - yy;
    
    return std::sqrt(dx * dx + dy * dy);
}