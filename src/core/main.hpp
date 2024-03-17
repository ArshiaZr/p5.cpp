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
#include <random>

class P5 {
public:
    // Instance
    static P5& getInstance();
    
    // public members
    unsigned int width;
    unsigned int height;
    unsigned int mouseX;
    unsigned int mouseY;
    int movedX;
    int movedY;
    unsigned int pmouseX;
    unsigned int pmouseY;
    std::string mouseButton;
    bool mouseIsPressed;
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
    Color color(Color color);
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

    void printColor(Color c);

    // Shape
    void arc(float x, float y, float w, float h, double start, double stop, ArcMode mode = ArcMode::PIE);
    void ellipse(float x, float y, float w, float h);
    void circle(float x, float y, float d);
    void line(float x1, float y1, float x2, float y2);
    void point(float x, float y);
    void point(Vector2f point);
    void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    // TODO: 3D
    // void point(sf::Vector3f point);
    // void point(float x, float y, float z);

    // void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    void rect(float x, float y, float w, float h, float tl = 0, float tr = 0, float br = 0, float bl = 0);
    void square(float x, float y, float s, float tl = 0, float tr = 0, float br = 0, float bl = 0);
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

    // ** Math **

    // calculations
    double abs(double value);
    double ceil(double value);
    double constrain(double value, double min, double max);
    double dist(double x1, double y1, double x2, double y2);
    double exp(double value);
    double floor(double value);
    double lerp(double start, double stop, double amt);
    double log(double value);
    double mag(double a, double b);
    double map(double value, double start1, double stop1, double start2, double stop2);
    double max(double a, double b);
    double max(std::vector<double> values);
    double min(double a, double b);
    double min(std::vector<double> values);
    double norm(double value, double start, double stop);
    double pow(double value, double exponent);
    double round(double value);
    double sq(double value);
    double sqrt(double value);
    double fract(double value);

    // random
    double randomSeed(unsigned int seed);
    double random(double min, double max);
    double random(double max);
    double random();
    double random(std::vector<double> values);
    float random(std::vector<float> values);
    int random(std::vector<int> values);
    // TODO: vector for random
    double randomGaussian(double mean, double sd);
    double randomGaussian(double sd);
    double randomGaussian();

    // noise
    double noiseSeed(unsigned int seed);
    double noise(double x, double y, double z);
    double noise(double x, double y);
    double noise(double x);


    // trigonometry
    AngleMode angleMode();
    void angleMode(AngleMode mode);

    // inverse of cosine expects -1 to 1
    // returns value 0 to PI
    double acos(double ratio);

    // inverse of sine expects -1 to 1
    // returns value -PI/2 to PI/2
    double asin(double ratio);

    // inverse of tangent expects -infinity to infinity
    // returns value -PI/2 to PI/2
    double atan(double ratio);

    // Calculates the angle formed by a specified point expecting y and x coordinates
    // returns value -PI to PI
    double atan2(double y, double x);

    // cosine
    // returns value -1 to 1
    double cos(double angle);

    // sine
    // returns value -1 to 1
    double sin(double angle);

    // tangent
    // returns value -infinity to infinity
    double tan(double angle);

    // Converts a radian measurement to its corresponding degree measurement
    double degrees(double radians);

    // Converts a degree measurement to its corresponding radian measurement
    double radians(double degrees);

    // setting
    void background(Color color);
    void background(unsigned int gray, unsigned int alpha);
    void background(unsigned int gray);
    void background(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha);
    void background(unsigned int v1, unsigned int v2, unsigned int v3);
    void fill(Color color);
    void fill(unsigned int gray, unsigned int alpha);
    void fill(unsigned int gray);
    void fill(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha);
    void fill(unsigned int v1, unsigned int v2, unsigned int v3);
    void noFill();
    void noStroke();
    void stroke(Color color);
    void stroke(unsigned int gray, unsigned int alpha);
    void stroke(unsigned int gray);
    void stroke(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha);
    void stroke(unsigned int v1, unsigned int v2, unsigned int v3);
    void strokeWeight(float weight);
    // void clear();
    void colorMode(ColorMode mode);
    // void erase();
    // void noErase();
    void ellipseMode(std::string mode);
    void rectMode(std::string mode);

    void createCanvas(int w, int h, GlMode mode = GlMode::P2D);
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

    AngleMode _angleMode;
    std::default_random_engine _randomGenerator;
    std::mt19937_64 _noiseGenerator;
    std::vector<int> _permutation{};

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
        
    // Events
    // void _mousePressed();
    // void _mouseReleased();
    // void _mouseClicked();
    // void _mouseMoved();
    // TODO 
    // doubleClicked()
    // mouseWheel()
    // requestPointerLock()
    // exitPointerLock()
    
    // mouseDragged()

    // TODO: validate parameters
    bool _isParametersValid(std::string name, std::vector<float> parameters);

    // Color
    std::vector<float> _colorFromHSB(std::vector<float> hsba);
    std::vector<float> _colorFromHSL(std::vector<float> hsla);
    std::vector<float>  _parseColorInputs(unsigned int r, unsigned int g, unsigned int b);
    std::vector<float>  _parseColorInputs(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

    // angles
    double _toRadians(double angle);
    double _toDegrees(double angle);
    double _fromRadians(double angle);
    double _fromDegrees(double angle);
};

#endif // MAIN_HPP