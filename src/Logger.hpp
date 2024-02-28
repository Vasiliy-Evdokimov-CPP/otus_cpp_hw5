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
            Логирующий метод
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
        std::cout << message << std::endl;
    }
};


void WriteLog(std::string message)
{
    std::cout << message << std::endl;
}