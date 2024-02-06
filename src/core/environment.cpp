#include "main.hpp"

double P5::frameRate(){
    return this->_frameRate;
}

void P5::frameRate(unsigned int fps){
    if(fps > 0){
        this->_targetFrameRate = fps;
    }
}

int P5::getTargetFrameRate(){
    return this->_targetFrameRate;
}

void P5::fullScreen(bool val){
    if(val){
        // full screen
    }else{
        // exit full screen
    }
}

bool P5::fullScreen(){
    return this->displayWidth == this->width && this->displayHeight == this->height;
}
