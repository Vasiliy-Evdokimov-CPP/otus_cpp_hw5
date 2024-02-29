#pragma once

/**
    \file
    \details
        В файле содержатся описание интерфейса логгирования и его консольная реализация
*/

#include <iostream>
#include <string>

/**
    \brief
        Интерфейс логгирования
*/
class ILogger
{
public:
    /**
        \brief
            Логгирующий метод
        \param message строка, записываемая в лог
    */
    virtual void WriteLog(std::string message) = 0;
};

/**
    \brief
        Консольный логгер
*/
class ConsoleLogger: public ILogger
{
public:
    virtual void WriteLog(std::string message) override
    {
        std::cout << "Console logger:\t" << message << std::endl;
    }
};

void WriteLog(std::string message)
{
    std::cout << "Default logging:\t" << message << std::endl;
}