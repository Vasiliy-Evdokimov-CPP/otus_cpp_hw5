#pragma once

/**
    \file
    \details
        В файле описывается вспомогательные типы
*/        

#include <string>
#include <cmath>
#include <map>

typedef unsigned int uint;

/**
    \brief
        Типы перьев
*/ 
enum class PenStyle { unknown, solid, dotted, dashed };

/**
    \brief
        Типы кистей
*/ 
enum class BrushStyle { unknown, solid, clear, horizontal, vertical };

/**
    \brief
        Цвета
*/ 
enum class Color { unknown, black, white, red, green, blue };

/**
    \brief
        Словарь соответствия стиля пера его названию 
*/ 
std::map<PenStyle, std::string> PenStyleToStringMap = 
{
    { PenStyle::unknown,    "(unknown)" }, 
    { PenStyle::solid,      "SOLID" }, 
    { PenStyle::dotted,     "DOTTED" }, 
    { PenStyle::dashed,     "DASHED" }
};

/**
    \brief
        Словарь соответствия стиля кисти его названию 
*/ 
std::map<BrushStyle, std::string> BrushStyleToStringMap = 
{
    { BrushStyle::unknown,      "(unknown)" }, 
    { BrushStyle::solid,        "SOLID" }, 
    { BrushStyle::clear,        "CLEAR" }, 
    { BrushStyle::horizontal,   "HORIZONTAL" },
    { BrushStyle::vertical,     "VERTICAL" }
};

/**
    \brief
        Словарь соответствия цвета его названию 
*/ 
std::map<Color, std::string> ColorToStringMap = 
{
    { Color::unknown,   "(unknown)" }, 
    { Color::black,     "BLACK" }, 
    { Color::white,     "WHITE" }, 
    { Color::red,       "RED" },
    { Color::green,     "GREEN" },
    { Color::blue,      "BLUE" }
};

/**
    \brief
        Преобразование стиля пера в строку
*/ 
std::string PenStyleToString(PenStyle pen_style) 
{
    if (PenStyleToStringMap.count(pen_style) == 0)
        return PenStyleToStringMap[PenStyle::unknown];
    //
    return PenStyleToStringMap[pen_style];     
}

/**
    \brief
        Преобразование стиля кисти в строку
*/
std::string BrushStyleToString(BrushStyle brush_style) 
{
    if (BrushStyleToStringMap.count(brush_style) == 0)
        return BrushStyleToStringMap[BrushStyle::unknown];
    //
    return BrushStyleToStringMap[brush_style];    
}

/**
    \brief
        Преобразование цвета в строку
*/
std::string ColorToString(Color color) 
{
    if (ColorToStringMap.count(color) == 0)
        return ColorToStringMap[Color::unknown];
    //
    return ColorToStringMap[color]; 
}

/**
    \brief
        Точка
*/
struct Point
{
    int x;
    int y;

    /**
        \brief
            Преобразование в строку
    */
    std::string ToString() 
    {
        return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
    }

    /**
        \brief
            Сериализация
    */
    std::string Serialize() 
    {
        return std::to_string(x) + " " + std::to_string(y);
    }
};

/**
    \brief
        Перо
*/
struct Pen 
{
    /**
        \brief
            Конструктор
    */
    Pen(): 
        style(PenStyle::solid),
        color(Color::black),
        thickness(1) {}
        
    /**
        \brief
            Стиль пера
    */
    PenStyle style;

    /**
        \brief
            Цвет
    */    
    Color color;

    /**
        \brief
            Толщина
    */    
    unsigned int thickness;

    /**
        \brief
            Преобразование в строку
    */
    std::string ToString()
    {
        return "(" +
            std::to_string(thickness) + "px; " +  
            PenStyleToString(style) + "; " + 
            ColorToString(color) + 
        ")";
    }
    
};

/**
    \brief
        Кисть
*/
struct Brush 
{
    /**
        \brief
            Конструктор
    */
    Brush():
        style(BrushStyle::solid),
        color(Color::white) {}

    /**
        \brief
            Стиль кисти
    */
    BrushStyle style;

    /**
        \brief
            Цвет
    */     
    Color color;
    
    /**
        \brief
            Преобразование в строку
    */
    std::string ToString()
    {
        return "(" + 
            BrushStyleToString(style) + "; " + 
            ColorToString(color) + 
        ")";
    }
};

/**
    \brief
        Вычисление расстояния от точки до отрезка
    \param p точка, расстояние от которой до отрезка вычисляем
    \param p1 первая точка отрезка
    \param p2 вторая точка отрезка 
*/
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