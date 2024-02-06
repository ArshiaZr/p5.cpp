#include "main.hpp"
#include <ctime>
#include "../utilities/time_date.hpp"

// since setup is called
long P5::millis(){
    return getCurrentTimeMillis() - this->_millisStart;
}

int P5::day() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_mday;
}

int P5::month() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_mon + 1; // Adding 1 to get the month in range 1-12
}

int P5::hour() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_hour;
}

int P5::minute() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_min;
}

int P5::second() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_sec;
}

int P5::year() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    return localTime->tm_year + 1900; // Adding 1900 to get the actual year
}