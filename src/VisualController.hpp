#pragma once

#include <vector>

#include "Logger.hpp"
#include "VisualObjects.hpp"

class VisualController 
{
private:
    void NewFile() {};
    void LoadFile() {};
    void SaveFile() {};
    //
    void AddObject(VisualObject& object) {};
    void DeleteObject(VisualObject& object) {};
    //
    std::vector<VisualObject*> objects;
public:
    VisualController() 
    {
        WriteLog(__PRETTY_FUNCTION__);        
    }
};