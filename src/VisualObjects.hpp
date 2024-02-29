#pragma once

/**
    \file
    \details
        В файле описывается классы визуальных объектов
*/

#include <vector>
#include <map>

#include "VisualTypes.hpp"
#include "VisualCanvas.hpp"

/**
    \brief
        Чувствительность при выделении объекта
*/        
const int HIT_TOLERANCE = 3;

/**
    \brief
        Типы визуальных объектов
*/ 
enum class VisualObjectType { unknown, selector, line, rectangle, ellipse };

/**
    \brief
        Словарь соответствия типа объекта его названию 
*/ 
std::map<VisualObjectType, std::string> ObjectTypeToStringMap = 
{
    { VisualObjectType::unknown,    "(unknown)" }, 
    { VisualObjectType::selector,   "SELECTOR" }, 
    { VisualObjectType::line,       "LINE" }, 
    { VisualObjectType::rectangle,  "RECTANGLE" }, 
    { VisualObjectType::ellipse,    "ELLIPSE" }
};

/**
    \brief
        Преобразование типа объекта в строку
*/ 
std::string ObjectTypeToString(VisualObjectType object_type)
{
    if (ObjectTypeToStringMap.count(object_type) == 0)
        return ObjectTypeToStringMap[VisualObjectType::unknown];
    //
    return ObjectTypeToStringMap[object_type];     
}

/**
    \brief
        Преобразование типа строки в тип объекта
*/ 
VisualObjectType StringToObjectType(std::string object_type)
{
    for(auto iter{ObjectTypeToStringMap.begin()}; iter != ObjectTypeToStringMap.end(); iter++)
        if (iter->second == object_type) 
            return iter->first;
    //        
    return VisualObjectType::unknown;
}

/**
    \brief
        Базовый класс визуальных объектов
*/
class BaseVisualObject {};

/**
    \brief
        Селектор - отдельное или групповое выделение объектов
*/
class Selector: public BaseVisualObject {};

/**
    \brief
        Визуальный объект - объекты непосредственно рисуемые в редакторе
*/
class VisualObject: public BaseVisualObject
{
public:
    /**
        \brief
            Конструктор
    */
    VisualObject()
    {        
        WriteLog("VisualObject()");
    }

    /**
        \brief
            Деструктор
    */
    ~VisualObject()
    {        
        WriteLog("~VisualObject()");
        //
        m_points.clear();
    }    

    /**
        \brief
            Получение количества точек
    */
    size_t GetPointsCount()
    {
        return m_points.size();
    }    

    /**
        \brief
            Получение максимального количества точек
        \details
            Например для обычной линии - всего две, а для полилинии - неограниченно
    */
    size_t GetMaxPointsCount()
    {
        return m_max_points_count;
    } 

    /**
        \brief
            Добавление точки
        \param point добавляемая точка
    */
    virtual void AddPoint(Point point)  
    {
        m_points.push_back(point);
    }

    /**
        \brief
            Завершено ли конструирование объекта
    */    
    int IsFinished() 
    {
        return (m_points.size() == GetMaxPointsCount());
    }

    /**
        \brief
            Сериализация объекта
    */   
    virtual std::string Serialize()
    {
        std::string res = ObjectTypeToString(m_type);
        //
        res += " " + std::to_string(m_points.size());
        //
        for (size_t i = 0; i < m_points.size(); ++i)
            res += " " + m_points[i].Serialize();
        //
        return res;    
    }

    /**
        \brief
            Возвращает наименовани етипа объекта
    */   
    virtual std::string GetTypeName()
    {
        return ObjectTypeToString(m_type);
    }

    /**
        \brief
            Рисование объекта
        \param canvas холст для рисования
    */
    virtual void Draw(std::shared_ptr<IVisualCanvas> canvas) = 0;

    /**
        \brief
            Проверка на попадание точки внутрь объекта
        \param point проверяема точка
    */
    virtual int HitTest(Point point) = 0;

    /**
        \brief
            Перо рисования объекта
    */
    Pen m_pen;
    
protected:
    /**
        \brief
            Максимальное количество точек
    */
    size_t m_max_points_count = 2;

    /**
        \brief
            Точки объекта
    */
    std::vector<Point> m_points;

    /**
        \brief
            Тип объекта
    */
    VisualObjectType m_type = VisualObjectType::unknown;
       
};

/**
    \brief
        Заполняемый объект
    \details
        Тот, у которого есть заливка
*/
class FilledVisualObject: public VisualObject
{   
public:
    /**
        \brief
            Кисть заливки
    */        
    Brush m_brush;
};

/**
    \brief
        Линейный объект
    \details
        Линии, полилинии, кривые и т.п.
*/
class LineVisualObject: public VisualObject
{
public:
    /**
        \brief
            Рисование объекта
        \param canvas холст для рисования
    */
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        canvas->m_pen = m_pen;    
        //
        for (size_t i = 1; i < m_points.size(); ++i)
            canvas->DrawLine(m_points[i - 1], m_points[i]);
    }

    /**
        \brief
            Проверка на попадание точки внутрь объекта
        \param point проверяема точка
    */
    int HitTest(Point point) override 
    {
        if (m_points.size() < 2) return 0;
        //
        return distance(point, m_points[0], m_points[1]) < HIT_TOLERANCE;
    }
};

/**
    \brief
        Прямоугольный объект
    \details
        Прямоугольники, квадраты, эллипсы и т.п.
*/
class RectVisualObject: public FilledVisualObject
{
public:
    /**
        \brief
            Проверка на попадание точки внутрь объекта
        \param point проверяема точка
    */
    int HitTest(Point point) 
    {
        if (m_points.size() < 2) return 0;
        //
        return 
            ((point.x > m_points[0].x - HIT_TOLERANCE) && (point.x < m_points[1].x + HIT_TOLERANCE) &&
             (point.y > m_points[0].y - HIT_TOLERANCE) && (point.y < m_points[1].y + HIT_TOLERANCE));        
    }

    /**
        \brief
            Конструктор
        \param pen перо рисования
        \param brush кисть рисования
    */
    RectVisualObject(Pen pen, Brush brush)
    {
        m_pen = pen;
        m_brush = brush;
    } 

    /**
        \brief
            Рисование объекта
        \param canvas холст для рисования
    */
    virtual void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        canvas->m_pen = m_pen;    
        canvas->m_brush = m_brush;    
    }
};

/**
    \brief
        Объект - простая линия
*/
class SimpleLine: public LineVisualObject
{
public:
    /**
        \brief
            Конструктор
    */
    SimpleLine()
    {    
        WriteLog("SimpleLine()");
        //
        m_max_points_count = 2;
        m_type = VisualObjectType::line;
    } 

    /**
        \brief
            Конструктор
        \param pen перо рисования
    */
    SimpleLine(Pen pen) : SimpleLine()
    {
        m_pen = pen;
    }    
};

/**
    \brief
        Объект - прямоугольник
*/
class Rectangle: public RectVisualObject
{
public:
    /**
        \brief
            Конструктор
        \param pen перо рисования
        \param brush кисть рисования
    */
    Rectangle(Pen pen, Brush brush) : RectVisualObject(pen, brush)
    {
        WriteLog("Rectangle()");
        //
        m_type = VisualObjectType::rectangle;
    };

    /**
        \brief
            Рисование объекта
        \param canvas холст для рисования
    */
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        RectVisualObject::Draw(canvas);
        //
        canvas->DrawRectangle(m_points[0], m_points[1]);
    }
};

/**
    \brief
        Объект - эллипс
*/
class Ellipse: public RectVisualObject
{
public:
    /**
        \brief
            Конструктор
        \param pen перо рисования
        \param brush кисть рисования
    */
    Ellipse(Pen pen, Brush brush) : RectVisualObject(pen, brush) 
    {
        WriteLog("Ellipse()");
        //
        m_type = VisualObjectType::ellipse;
    };
    
    /**
        \brief
            Рисование объекта
        \param canvas холст для рисования
    */
    void Draw(std::shared_ptr<IVisualCanvas> canvas) override
    {
        RectVisualObject::Draw(canvas);
        //
        canvas->DrawEllipse(m_points[0], m_points[1]);
    }
}; 