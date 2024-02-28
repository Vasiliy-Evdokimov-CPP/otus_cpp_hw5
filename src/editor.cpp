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

#include "VisualController.hpp"
#include "VisualEditor.hpp"

int main()
{
    std::shared_ptr<VisualController> visual_controller = std::make_shared<VisualController>();
    DesktopEditor desktop_editor(visual_controller);
    //
    //  creating new file
    desktop_editor.NewFile();
    //  draw the line
    desktop_editor.SelectPenColor(Color::green);
    desktop_editor.SelectObjectType(VisualObjectType::line);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left);  
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //  draw the rectangle, but cancel via right mouse button
    desktop_editor.SelectObjectType(VisualObjectType::rectangle);
    desktop_editor.MouseDown(Point{30, 30}, MouseButton::left); 
    desktop_editor.MouseDown(Point{40, 40}, MouseButton::right);
    //  draw the ellipse
    desktop_editor.SelectBrushColor(Color::red);
    desktop_editor.SelectBrushStyle(BrushStyle::vertical);
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{50, 50}, MouseButton::left); 
    desktop_editor.MouseDown(Point{60, 60}, MouseButton::left);
    //  select and delete the ellipse
    desktop_editor.SelectObjectType(VisualObjectType::selector);
    desktop_editor.MouseDown(Point{55, 55}, MouseButton::left); 
    desktop_editor.KeyPress(KeyboardKey::vk_delete);
    //  draw the another ellipse
    desktop_editor.SelectPenStyle(PenStyle::dotted);
    desktop_editor.SelectBrushColor(Color::green);
    desktop_editor.SelectBrushStyle(BrushStyle::horizontal);    
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left); 
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //
    //  saving file
    desktop_editor.SaveFile("new_picture.txt");
    //  loading file
    desktop_editor.LoadFile("new_picture.txt");
    //
    return 0;
}