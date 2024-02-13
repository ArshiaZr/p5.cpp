#include "main.hpp"

// Public functions
void P5::colorMode(ColorMode mode){
    this->_renderer->setColorMode(mode);
}

void P5::background(Color color){
    Color c = this->color(color.r, color.g, color.b, color.a);
    this->_window.clear(sf::Color(c.r, c.g, c.b, c.a));
}

void P5::background(unsigned int gray, unsigned int alpha){
    this->background(Color(gray, gray, gray, alpha));
}

void P5::background(unsigned int gray){
    this->background(gray, 255);
}

void P5::background(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha){
    this->background(Color(v1, v2, v3, alpha));
}

void P5::background(unsigned int v1, unsigned int v2, unsigned int v3){
    this->background(v1, v2, v3, 255);
}

void P5::fill(Color color){
    Color c = this->color(color.r, color.g, color.b, color.a);
    this->_renderer->setFillColor(c);
    this->_renderer->setDoFill(true);
}

void P5::fill(unsigned int gray, unsigned int alpha){
    this->fill(Color(gray, gray, gray, alpha));
}

void P5::fill(unsigned int gray){
    this->fill(gray, 255);
}

void P5::fill(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha){
    this->fill(Color(v1, v2, v3, alpha));
}

void P5::fill(unsigned int v1, unsigned int v2, unsigned int v3){
    this->fill(v1, v2, v3, 255);
}

void P5::noFill(){
    this->_renderer->setDoFill(false);
}

void P5::noStroke(){
    this->_renderer->setDoStroke(false);
}

void P5::stroke(Color color){
    Color c = this->color(color.r, color.g, color.b, color.a);
    this->_renderer->setStrokeColor(c);
    this->_renderer->setDoStroke(true);
}

void P5::stroke(unsigned int gray, unsigned int alpha){
    this->stroke(Color(gray, gray, gray, alpha));
}

void P5::stroke(unsigned int gray){
    this->stroke(gray, 255);
}

void P5::stroke(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha){
    this->stroke(Color(v1, v2, v3, alpha));
}

void P5::stroke(unsigned int v1, unsigned int v2, unsigned int v3){
    this->stroke(v1, v2, v3, 255);
}

void P5::strokeWeight(float weight){
    this->_renderer->setStrokeWeight(weight);
}

void P5::ellipseMode(std::string mode){
    if(mode == CENTER || mode == RADIUS || mode == CORNER || mode == CORNERS){
        this->_renderer->setEllipseMode(mode);
    }
}

void P5::rectMode(std::string mode){
     if(mode == CENTER || mode == RADIUS || mode == CORNER || mode == CORNERS){
        this->_renderer->setRectMode(mode);
    }
}