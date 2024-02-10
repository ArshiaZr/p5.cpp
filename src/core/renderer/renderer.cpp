#include "renderer.hpp"
#include <iostream>

// Constructor
Renderer::Renderer(){
    this->_clipping = false;
    this->_clipInvert = false;

    this->_rectMode = CORNER;
    this->_ellipseMode = CENTER;
    this->_curveTightness = 0.f;
    this->_colorMode = ColorMode::RGB;
    this->_context = std::stack<std::unordered_map<std::string, ContextValues>>();
}



// Public API functions

void Renderer::push(){
    this->_context.push({
        {"clipping", this->_clipping},
        {"clipInvert", this->_clipInvert},
        {"rectMode", this->_rectMode},
        {"ellipseMode", this->_ellipseMode},
        {"curveTightness", this->_curveTightness},
        {"colorMode", this->_colorMode}
    });
}
void Renderer::pop(){
    if(this->_context.size() > 0){
        std::unordered_map<std::string, ContextValues> context = this->_context.top();
        this->_context.pop();
        this->_clipping = std::get<bool>(context["clipping"]);
        this->_clipInvert = std::get<bool>(context["clipInvert"]);
        this->_rectMode = std::get<std::string>(context["rectMode"]);
        this->_ellipseMode = std::get<std::string>(context["ellipseMode"]);
        this->_curveTightness = std::get<double>(context["curveTightness"]);
        this->_colorMode = std::get<ColorMode>(context["colorMode"]);
    }else{
        std::cout << "Error: No context to pop" << std::endl;
    }
}

void Renderer::setColorMode(ColorMode mode){
    this->_colorMode = mode;
}

ColorMode Renderer::getColorMode(){
    return std::get<ColorMode>(this->_colorMode);
}