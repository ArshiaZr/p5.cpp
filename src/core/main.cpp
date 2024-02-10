#include "main.hpp"
#include <iostream>
#include <thread>
#include <chrono> 
#include "../utilities/time_date.hpp"

// Constructor implementation
P5::P5() {
    this->_initialize();
    this->_window.create(sf::VideoMode(this->width, this->height), "p5", sf::Style::Default, sf::ContextSettings(0, 0, 2));
    this->_desktop = sf::VideoMode::getDesktopMode();
    this->_setDisplaySize();
}

// Destructor implementation
P5::~P5(){
    this->_window.close();
    delete this->_renderer;
}

// public functions
void P5::registerMethod(std::string method, std::function<void()> callback){
    this->_registeredMethods[method] = callback;
}

// private functions
void P5::_setSize(unsigned int w, unsigned int h){
    this->width = w;
    this->height = h;
}

void P5::_setDisplaySize(){
    this->displayWidth = this->_desktop.width / 2;
    // TODO: - fix this
    this->displayHeight = this->_desktop.height / 2;
}

void P5::_initialize(){
    this->_renderer = new Renderer();
    this->_millisStart = -1;
    this->_setSize(100, 100);
    this->frameCount = 0;
    this->deltaTime = 0;
    this->_frameRate = 0;
    this->_targetFrameRate = 60;
    this->glVersion = GlMode::P2D;
    // TODO: get acutal value of displayWidth and displayHeight
    this->_registeredMethods = {};
    this->glVersion = GlMode::P2D;
    this->_angleMode = AngleMode::RADIANS;
}

void P5::_setup(){
    if(this->_registeredMethods["setup"]){
        this->_callMethod("setup");
        this->_millisStart = getCurrentTimeMillis();
        this->_updateWebglMode();
        this->_updateWindowSize();
        this->_centerWindow();
    }
}

void P5::_draw(){
    if(this->_registeredMethods["draw"]){

        this->_window.clear();
        this->_callMethod("draw");
        this->_window.display();
    }
}

void P5::_callMethod(std::string method){
    if(this->_registeredMethods[method]){
        this->_registeredMethods[method]();
    }
}

void P5::_manageEvents(){
    sf::Event event;
    while(this->_window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                this->_window.close();
                break;
            case sf::Event::Resized:
                this->_setSize(event.size.width, event.size.height);
                if(this->_registeredMethods["windowResized"]){
                    this->_callMethod("windowResized");
                }
                break;
            default:
            break;
        }
    }
}

void P5::_updateWindowSize(){
    if(this->width != this->_window.getSize().x || this->height != this->_window.getSize().y){
        this->_window.setSize(sf::Vector2u(this->width, this->height));
    }
}

void P5::_centerWindow(){
    this->_window.setPosition(sf::Vector2i(this->displayWidth / 2 - this->width / 2, this->displayHeight / 2 - this->height / 2));
}

void P5::_updateWebglMode(){
    // TODO: - impelemnt gl version mode
    this->_window.setActive(false);
    switch(this->glVersion){
        case GlMode::P2D:
            this->_window.create(sf::VideoMode(this->width, this->height), "p5", sf::Style::Default, sf::ContextSettings(0, 0, 2));
            break;
        case GlMode::WEBGL:
            // this->_window.create(sf::VideoMode(this->width, this->height), "p5", sf::Style::Default, sf::ContextSettings(0, 0, 2));
            break;
        default:
            break;
    }
    this->_window.setActive(true);
}

// TODO: validate parameters
bool P5::_isParametersValid(std::string name, std::vector<float> parameters){
    return true;
}

void P5::push(){
    this->_renderer->push();
}

void P5::pop(){
    this->_renderer->pop();
}

void P5::run(){
    this->_setup();

    long beforeTime = getCurrentTimeNanos();
    long overSleepTime = 0L;

    while(this->_window.isOpen()){
        // events;
        this->_manageEvents();

        this->_draw();

        // Check if the frame rate is too high
        // calculates sleep time
        // Set the frame rate
        long afterTime = getCurrentTimeNanos();
        long timeDiff = afterTime - beforeTime;
        this->deltaTime = convertNanosToMillis(timeDiff);

        long sleepTime = ((1000000000L / this->_targetFrameRate) - timeDiff) - overSleepTime;
       
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(sleepTime));
            overSleepTime = (getCurrentTimeNanos() - afterTime) - sleepTime;
        } else {
            overSleepTime = 0L;
        }

        this->deltaTime += convertNanosToMillis(sleepTime) + convertNanosToMillis(overSleepTime);

        beforeTime = getCurrentTimeNanos();

        if(this->deltaTime > 0){
            this->_frameRate = 1000.0f / this->deltaTime;
        }else{
            this->_frameRate = this->_targetFrameRate;
        }        
        this->frameCount++;
    }

}