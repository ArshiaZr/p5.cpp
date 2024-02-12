#include "../main.hpp"
#include <math.h>
#include <iostream>

// public functions
void P5::angleMode(AngleMode mode){
    this->_angleMode = mode;
}

AngleMode P5::angleMode(){
    return this->_angleMode;
}

double P5::acos(double ratio){
    return this->_fromRadians(std::acos(ratio));
}

double P5::asin(double ratio){
    return this->_fromRadians(std::asin(ratio));
}

double P5::atan(double ratio){
    return this->_fromRadians(std::atan(ratio));
}

double P5::atan2(double y, double x){
    return this->_fromRadians(std::atan2(y, x));
}

double P5::cos(double angle){
    return std::cos(this->_toRadians(angle));
}

double P5::sin(double angle){
    return std::sin(this->_toRadians(angle));
}

double P5::tan(double angle){
    return std::tan(this->_toRadians(angle));
}

double P5::degrees(double angle){
    return angle * RAD_TO_DEG;
}

double P5::radians(double angle){
    return angle * DEG_TO_RAD;
}

double P5::_toRadians(double angle){
    if(this->_angleMode == AngleMode::DEGREES){
        return angle * DEG_TO_RAD;
    }
    return angle;
}

double P5::_toDegrees(double angle){
    if(this->_angleMode == AngleMode::RADIANS){
        return angle * RAD_TO_DEG;
    }
    return angle;
}

double P5::_fromRadians(double angle){
    if(this->_angleMode == AngleMode::DEGREES){
        return angle * RAD_TO_DEG;
    }
    return angle;
}

double P5::_fromDegrees(double angle){
    if(this->_angleMode == AngleMode::RADIANS){
        return angle * DEG_TO_RAD;
    }
    return angle;
}