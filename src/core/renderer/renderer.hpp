// File: renderer.hpp

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../constants.hpp"
#include <variant>
#include <unordered_map>
#include <string>
#include <stack>

class Renderer {
public:
    // public members

    // Constructor
    Renderer();

    // *************************
    // * Public API functions *
    // *************************

    void setColorMode(ColorMode mode);
    ColorMode getColorMode();

    // Context
    void push();
    void pop();

private:
    // *************************
    // * Private members *
    // *************************
    ContextValues _clipping;
    ContextValues _clipInvert;
    ContextValues _rectMode;
    ContextValues _ellipseMode;
    ContextValues _curveTightness;
    ContextValues _colorMode;

    // context
    std::stack<std::unordered_map<std::string, ContextValues>> _context;


    // unsigned int _pushPopDepth;

    // *************************
    // * Private API functions *
    // *************************

};


#endif