// File: main.hpp

#ifndef MAIN_HPP
#define MAIN_HPP

#include "constants.hpp"
#include "renderer/renderer.hpp"
#include <string>
#include <unordered_map>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>

class Color: public sf::Color {
    public:
    // Inherit constructors from sf::Color
    using sf::Color::Color;
};


class P5 {
public:
    // public members
    unsigned int width;
    unsigned int height;
    long frameCount;
    double deltaTime;
    unsigned int displayWidth;
    unsigned int displayHeight;
    GlMode glVersion;
    
    // Constructor
    P5();

    // decstructor
    ~P5();

    // *************************
    // * Public API functions *
    // *************************

    // Enviqronment
    double frameRate();
    void frameRate(unsigned int fps);
    int getTargetFrameRate();
    
    void fullScreen(bool val);
    bool fullScreen();

    // Date and Time
    int day();
    int hour();
    int minute();
    long millis();
    int month();
    int second();
    int year();

    // Context
    void push();
    void pop();

    // Color
    unsigned int alpha(Color color);
    unsigned int blue(Color color);
    unsigned int brightness(Color color);
    Color color(unsigned int gray);
    Color color(unsigned int gray, unsigned int alpha);
    Color color(unsigned int v1, unsigned int v2, unsigned int v3);
    Color color(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha);
    unsigned int green(Color color);
    unsigned int hue(Color color);
    Color lerpColor(Color c1, Color c2, double amt);
    unsigned int lightness(Color color);
    unsigned int red(Color color);
    unsigned int saturation(Color color);
    // TODO: implement maxes
    void colorMode(ColorMode mode);
    void printColor(Color c);

    // Shape
    void arc(float x, float y, float w, float h, float start, float stop, ArcMode mode = ArcMode::CHORD);
    void ellipse(float x, float y, float w, float h);
    void circle(float x, float y, float d);
    void line(float x1, float y1, float x2, float y2);
    void point(float x, float y);
    void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    void rect(float x, float y, float w, float h);
    void square(float x, float y, float s);
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

    void createCanvas(int w, int h, GlMode mode);
    void registerMethod(std::string method, std::function<void()> callback);
    void run();

private:
    // *************************
    // * Private members *
    // *************************
    sf::RenderWindow _window;
    sf::VideoMode _desktop;
    Renderer *_renderer;
    double _frameRate;
    int _targetFrameRate;
    bool _loop;
    int _millisStart;
    unsigned int _colorMaxes[3][4] = {
        {255, 255, 255, 255},
        {360, 100, 100, 255},
        {360, 100, 100, 255}
    };
    std::unordered_map<std::string, std::function<void()>> _registeredMethods;

    // *************************
    // * Private API functions *
    // *************************
    void _initialize();
    void _setSize(unsigned int w, unsigned int h);
    void _setDisplaySize();
    void _setup();
    void _draw();
    void _callMethod(std::string method);
    void _manageEvents();
    void _updateWindowSize();
    void _centerWindow();
    void _updateWebglMode();
    // TODO: validate parameters
    bool _isParametersValid(std::string name, std::vector<float> parameters);
    float _toRadians(float degrees);
    float _toDegrees(float radians);

    // Color
    std::vector<float> _colorFromHSB(std::vector<float> hsba);
    std::vector<float> _colorFromHSL(std::vector<float> hsla);
    std::vector<float>  _parseColorInputs(unsigned int r, unsigned int g, unsigned int b);
    std::vector<float>  _parseColorInputs(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
};

#endif // MAIN_HPP