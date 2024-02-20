#include <vector>
#include "VisualTypes.hpp"
#include "VisualObjects.hpp"

template <typename T>
std::enable_if_t<
    std::is_same<T, SimpleLine>::value ||
    std::is_same<T, PolyLine>::value ||
    std::is_same<T, Rectangle>::value ||
    std::is_same<T, Ellipse>::value>
SelectObject(T object) 
{
    //
}

void SelectPenStyle(PenStyle pen_style)
{
    //
}

void SelectBrushStyle(BrushStyle brush_style)
{
    //
}

void SelectColor(Color color)
{
    //
}

void SelectThickness(int thickness)
{
    //
}

