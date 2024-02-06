// File: main.hpp

#ifndef MAIN_HPP
#define MAIN_HPP

#include "constants.hpp"
#include <string>
#include <unordered_map>
#include <functional>
#include <SFML/Graphics.hpp>


class P5 {
public:
    // public members
    unsigned int width;
    unsigned int height;
    long frameCount;
    double deltaTime;
    int displayWidth;
    int displayHeight;
    WebglMode webglVersion;
    
    // Constructor
    P5();

    // public functions
    double frameRate();
    void frameRate(int fps);
    int getTargetFrameRate();
    void createCanvas(int w, int h, WebglMode mode);
    
    void fullScreen(bool val);
    bool fullScreen();

    int day();
    int hour();
    int minute();
    long millis();
    int month();
    int second();
    int year();

    void registerMethod(std::string method, std::function<void()> callback);
    
    void run();

private:
    // members
    sf::RenderWindow _window;
    sf::VideoMode _desktop;
    double _frameRate;
    int _targetFrameRate;
    bool _loop;
    int _millisStart;
    ColorMode _colorMode;
   
    // std::unordered_map<std::string, int[4]> _colorMaxes;

    std::unordered_map<std::string, std::function<void()>> _registeredMethods;
    // TODO: events

    // private functions
    void _initialize();
    void _setSize(unsigned int w, unsigned int h);
    void _setDisplaySize();
    void _setup();
    void _draw();
    void _callMethod(std::string method);
    void _manageEvents();
    void _updateWindowSize();
    void _centerWindow();
};

#endif // MAIN_HPP