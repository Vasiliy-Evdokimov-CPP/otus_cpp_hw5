
#include "VisualController.hpp"
#include "VisualEditor.hpp"

int main()
{
    std::shared_ptr<VisualController> visual_controller = std::make_shared<VisualController>();
    DesktopEditor desktop_editor(visual_controller);
    //
    //  создание нового файла
    desktop_editor.NewFile();
    //  рисование линии
    desktop_editor.SelectPenColor(Color::green);
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
    //  выделение и удаление эллипса
    desktop_editor.SelectObjectType(VisualObjectType::selector);
    desktop_editor.MouseDown(Point{55, 55}, MouseButton::left); 
    desktop_editor.KeyPress(KeyboardKey::vk_delete);
    //  рисование ещё одного эллипса
    desktop_editor.SelectPenStyle(PenStyle::dotted);
    desktop_editor.SelectBrushColor(Color::green);
    desktop_editor.SelectBrushStyle(BrushStyle::horizontal);    
    desktop_editor.SelectObjectType(VisualObjectType::ellipse);
    desktop_editor.MouseDown(Point{10, 10}, MouseButton::left); 
    desktop_editor.MouseDown(Point{20, 20}, MouseButton::left);
    //
    //  сохранение файла
    desktop_editor.SaveFile("new_picture.txt");
    //  загрузка файла
    //  desktop_editor.LoadFile("new_picture.txt");
    //
    return 0;
}