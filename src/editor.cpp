/**
    \file
    \brief 
        OTUS C++ Professional Домашнее задание №5
    \details
        Спроектировать простейший графический векторный редактор. Подготовить макеты классов, отражающих структуру будущего проекта.
        Функционал для макетирования следующий:
        - создание нового документа
        - импорт документа из файла
        - экспорт документа в файл
        - создание графического примитива
        - удаление графического примитива
        Основной упор сделать на шаблон контроллера (MVC) и полиморфизм. Функции, являющиеся обработчиками GUI, собрать в одном файле с функцией `main`.
        Внимание должно быть сосредоточено на декларациях, реализация только в крайнем случае для минимальной демонстрации необходимых вызовов. Проект должен компилироваться, все заголовки должны пройти стадию компиляции.
        Задание считается выполненным успешно, если все файлы прошли стадию компиляции, все классы охвачены диаграммами, код успешно прошел анализ.
*/

#include "Logger.hpp"
#include "VisualController.hpp"
#include "VisualEditor.hpp"

int main()
{
    DesktopEditor desktop_editor(
        std::make_shared<VisualController>(
            std::make_shared<ConsoleLogger>()
        )
    );
    //
    //  создание нового документа
    desktop_editor.NewFile();
    //  рисуем линию
    desktop_editor.SelectPenColor(Color::green);
    desktop_editor.SelectObjectType(VisualObjectType::line);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left);  
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //  начинаем рисовать прямоугольник, но отменяем, нажимая ПКМ
    desktop_editor.SelectObjectType(VisualObjectType::rectangle);
    desktop_editor.MouseDown(Point{30, 30}, MouseButton::left); 
    desktop_editor.MouseDown(Point{40, 40}, MouseButton::right);
    //  рисуем эллипс
    desktop_editor.SelectBrushColor(Color::red);
    desktop_editor.SelectBrushStyle(BrushStyle::vertical);
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{50, 50}, MouseButton::left); 
    desktop_editor.MouseDown(Point{60, 60}, MouseButton::left);
    //  выбираем и удаляем эллипс
    desktop_editor.SelectObjectType(VisualObjectType::selector);
    desktop_editor.MouseDown(Point{55, 55}, MouseButton::left); 
    desktop_editor.KeyPress(KeyboardKey::vk_delete);
    //  рисуем ещё один эллипс
    desktop_editor.SelectPenStyle(PenStyle::dotted);
    desktop_editor.SelectBrushColor(Color::green);
    desktop_editor.SelectBrushStyle(BrushStyle::horizontal);    
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left); 
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //
    //  сохраняем файл
    desktop_editor.SaveFile("new_picture.txt");
    //  загружаем файл
    desktop_editor.LoadFile("new_picture.txt");
    //
    return 0;
}