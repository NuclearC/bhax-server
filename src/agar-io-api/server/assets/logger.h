/*
    AgarAPI Server version 0.0.0.1a
    Copyright (c) 2016 Bhax Development team
*/

#include <iostream>

class Logger {
    std::string Name = "logger";
public:
    int logLvl = 5; //Log level 0-5
    void log (int msgLvl, const std::string msg);
    void set_name (const std::string msg);
};

void Logger::set_name (const std::string name) {
    Name = name;
}

void Logger::log (int msgLvl, const std::string msg) {
    if (logLvl == 0 || logLvl <= msgLvl) {
        return;
    }
    if (logLvl >= msgLvl) {
        std::cout << "[ " << Name << " ] " << msg << std::endl;
        return;
    }
}