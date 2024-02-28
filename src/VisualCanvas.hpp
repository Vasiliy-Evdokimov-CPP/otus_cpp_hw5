#pragma once

/**
    \file
    \details
        В файле описывается интерфейс виртуальнрого холста и его desktop-реализация.
        Соответственно, могут быть реализованы другие виды холстов - web, mobile ...
*/

#include "Logger.hpp"
#include "VisualTypes.hpp"

/**
    \brief
        Интерфейс холста
    \details
        Декларируются методы рисования графических примитивов на холсте
*/
class IVisualCanvas 
{
public:
    virtual void DrawLine(Point point_1, Point point_2) = 0;
    virtual void DrawRectangle(Point left_top, Point right_bottom) = 0;
    virtual void DrawEllipse(Point left_top, Point right_bottom) = 0;
    
    void Clear()
    {
        WriteLog("Canvas has been cleared!");
    }

    Pen m_pen;
    Brush m_brush;
};

//

/**
    \brief
        Desktop холст
    \details
        Реализует методы рисования графических примитивов на холсте в desktop-приложении
*/
class DesktopCanvas: public IVisualCanvas
{
    void DrawLine(Point point_1, Point point_2) override;
    void DrawRectangle(Point left_top, Point right_bottom) override;
    void DrawEllipse(Point left_top, Point right_bottom) override;
};

/**
    \brief
        Рисование линии
    \details
        Метод рисования линии
    \param point_1 точка №1
    \param point_2 точка №2
*/
void DesktopCanvas::DrawLine(Point point_1, Point point_2)
{
    WriteLog("DesktopCanvas_Draw LINE from " +
        point_1.ToString() + " to " + point_2.ToString() +
        " with pen " + m_pen.ToString()
    );
} 

/**
    \brief
        Рисование приямоугольника
    \details
        Метод рисования прямоугольника
    \param left_top верхний левый угол
    \param right_bottom нижний правый угол
*/
void DesktopCanvas::DrawRectangle(Point left_top, Point right_bottom)
{
    WriteLog("DesktopCanvas_Draw RECTANGLE from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_pen.ToString() + 
        " and brush " + m_brush.ToString()
    );        
} 

/**
    \brief
        Рисование эллипса
    \details
        Метод рисования эллипса
    \param left_top верхний левый угол описывающего прямоугольника
    \param right_bottom нижний правый угол описывающего прямоугольника
*/
void DesktopCanvas::DrawEllipse(Point left_top, Point right_bottom)
{
    WriteLog("DesktopCanvas_Draw ELLIPSE from " + 
        left_top.ToString() + " to " + right_bottom.ToString() + 
        " with pen " + m_pen.ToString() +
        " and brush " + m_brush.ToString()
    );        
} 

