#pragma once

/**
    \file
    \details
        В файле описывается интерфейс виртуальнрого холста и его desktop-реализация.
        Холст отвечает за масштабирование объектов (преобразования логических координат в физические), скроллинг и т.п.
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
    /**
        \brief
            Конвертация логических координат в координаты холста
        \param point конвертируемая точка   
    */
    virtual Point ConvertLogToPhys(Point point) = 0;

    /**
        \brief
            Рисование линии
    */        
    virtual void DrawLine(Point point_1, Point point_2) = 0;

    /**
        \brief
            Рисование прямоугольника
    */ 
    virtual void DrawRectangle(Point left_top, Point right_bottom) = 0;

    /**
        \brief
            Рисование эллипса
    */ 
    virtual void DrawEllipse(Point left_top, Point right_bottom) = 0;   

    /**
        \brief
            Очищение холста
    */
    void Clear()
    {
        WriteLog("Canvas has been cleared!");
    }

    /**
        \brief
            Установка масштаба
        \param scale масштаб    
    */
    void SetScale(int scale)
    {
        m_scale = scale;
    }

    /**
        \brief
            Перо рисования
    */
    Pen m_pen;
    
    /**
        \brief
            Кисть рисования
    */
    Brush m_brush;
private:    
    int m_scale;
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
    Point ConvertLogToPhys(Point point) override;
    void DrawLine(Point point_1, Point point_2) override;
    void DrawRectangle(Point left_top, Point right_bottom) override;
    void DrawEllipse(Point left_top, Point right_bottom) override;
};

/**
    \brief
        Конвертация логических координат в координаты холста
    \param point конвертируемая точка   
*/
 Point DesktopCanvas::ConvertLogToPhys(Point point)
 {
    //  здесь производится конвертация точки с учётов масштаба и скроллинга холста
    return point;
 }

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
    Point pt1 = ConvertLogToPhys(point_1);
    Point pt2 = ConvertLogToPhys(point_2);
    //
    WriteLog("DesktopCanvas_Draw LINE from " +
        pt1.ToString() + " to " + pt2.ToString() +
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
    Point pt1 = ConvertLogToPhys(left_top);
    Point pt2 = ConvertLogToPhys(right_bottom);
    //
    WriteLog("DesktopCanvas_Draw RECTANGLE from " + 
        pt1.ToString() + " to " + pt2.ToString() + 
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
    Point pt1 = ConvertLogToPhys(left_top);
    Point pt2 = ConvertLogToPhys(right_bottom);
    //
    WriteLog("DesktopCanvas_Draw ELLIPSE from " + 
        pt1.ToString() + " to " + pt2.ToString() + 
        " with pen " + m_pen.ToString() +
        " and brush " + m_brush.ToString()
    );        
} 

