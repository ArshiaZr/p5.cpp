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
    void setDoStroke(bool val);
    void setStrokeColor(Color color);
    double getStrokeWeight();
    void setStrokeWeight(double weight);
    
    bool getDoFill();
    void setDoFill(bool val);
    void setFillColor(Color color);

    std::string getEllipseMode();
    void setEllipseMode(std::string mode);

    std::string getRectMode();
    void setRectMode(std::string mode);

    // Context
    void push();
    void pop();

    // shape
    void _arc(float x, float y, float w, float h, double start, double stop, ArcMode mode, sf::RenderWindow &window);
    void _ellipse(float x, float y, float w, float h, sf::RenderWindow &window);
    void _line(float x1, float y1, float x2, float y2, sf::RenderWindow &window);
    void _point(float x, float y, sf::RenderWindow &window);
    void _quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, sf::RenderWindow &window);
    void _rect(float x, float y, float w, float h, float tl, float tr, float br, float bl, sf::RenderWindow &window);
    void _triangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::RenderWindow &window);

private:
    // *************************
    // * Private members *
    // *************************
    // ContextValues _clipping;
    // ContextValues _clipInvert;
    ContextValues _ellipseMode;   
    ContextValues _rectMode;
    ContextValues _curveTightness;
    ContextValues _colorMode;
    ContextValues _doStroke;
    ContextValues _strokeColor;
    ContextValues _strokeWeight;
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