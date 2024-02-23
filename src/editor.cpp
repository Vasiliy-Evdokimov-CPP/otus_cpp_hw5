
#include "VisualController.hpp"
#include "VisualEditor.hpp"

int main()
{
    VisualController visual_controller;
    DesktopEditor desktop_editor(&visual_controller);
    //
    // создание нового файла
    desktop_editor.NewFile();
    //  рисование линии
    desktop_editor.SelectObjectType(VisualObjectType::line);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left);  
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //  начало рисования прямоугольника, но отмена по нажатию на правую кнопку мыши    
    desktop_editor.SelectObjectType(VisualObjectType::rectangle);
    desktop_editor.MouseDown(Point{30, 30}, MouseButton::left); 
    desktop_editor.MouseDown(Point{40, 40}, MouseButton::right);
    //  рисование эллипса
    desktop_editor.SelectBrushColor(Color::red);
    desktop_editor.SelectBrushStyle(BrushStyle::vertical);
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{50, 50}, MouseButton::left); 
    desktop_editor.MouseDown(Point{60, 60}, MouseButton::left);
    //
    //  сохранение файла
    desktop_editor.SaveFile("new_picture.json");
    //  загрузка файла
    desktop_editor.LoadFile("new_picture.json");
    //
    return 0;
}

/* 
std::unique_ptr<Class> x
x = std::make_unique<Class>()
*/