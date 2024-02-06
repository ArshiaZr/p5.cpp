#include "time_date.hpp"
#include <chrono>

long getCurrentTimeMillis(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();  
}

long getCurrentTimeNanos(){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();  
}

double convertNanosToMillis(long nanos) {
    return nanos / 1000000.0f;
}