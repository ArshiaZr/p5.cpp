// File: random.cpp
#include "main.hpp"
#include <stdlib.h>

double P5::randomSeed(unsigned int seed) {
    this->_randomGenerator.seed(seed);
}

double P5::random(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(this->_randomGenerator);
}

double P5::random(double max) {
    return this->random(0, max);
}

double P5::random() {
    return this->random(1);
}

double P5::random(std::vector<double> values) {
    return values[static_cast<int>(this->random(0, values.size()))];
}

float P5::random(std::vector<float> values) {
    return values[static_cast<int>(this->random(0, values.size()))];
}

int P5::random(std::vector<int> values) {
    return values[static_cast<int>(this->random(0, values.size()))];
}

double P5::randomGaussian(double mean, double sd) {
    double x1, x2, w, y1, y2;
    do {
        x1 = 2.0 * this->random() - 1.0;
        x2 = 2.0 * this->random() - 1.0;
        w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);
    w = std::sqrt((-2.0 * std::log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;
    return mean + y1 * sd;
}

double P5::randomGaussian(double sd) {
    return this->randomGaussian(0, sd);
}

double P5::randomGaussian() {
    return this->randomGaussian(0, 1);
}