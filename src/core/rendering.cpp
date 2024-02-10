#include "main.hpp"

// public functions
void P5::createCanvas(int w, int h, GlMode mode = GlMode::P2D){
    // TODO: implement canvasModes
    this->glVersion = mode;
    this->width = w;
    this->height = h;
}