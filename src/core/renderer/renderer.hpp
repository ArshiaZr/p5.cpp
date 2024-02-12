// File: renderer.hpp

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../constants.hpp"
#include <variant>
#include <unordered_map>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>


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

    bool getDoStroke();
    bool getDoFill();

    std::string getEllipseMode();

    // Context
    void push();
    void pop();

    // shape
    void _arc(float x, float y, float w, float h, double start, double stop, ArcMode mode, sf::RenderWindow &window);

    void _ellipse(float x, float y, float w, float h);

private:
    // *************************
    // * Private members *
    // *************************
    // ContextValues _clipping;
    // ContextValues _clipInvert;
    ContextValues _rectMode;
    ContextValues _ellipseMode;
    ContextValues _curveTightness;
    ContextValues _colorMode;
    ContextValues _doStroke;
    ContextValues _strokeColor;
    ContextValues _doFill;
    ContextValues _fillColor;


    // context
    std::stack<std::unordered_map<std::string, ContextValues>> _context;


    // unsigned int _pushPopDepth;

    // *************************
    // * Private API functions *
    // *************************

};


#endif