// File: calculations.cpp
#include "main.hpp"
#include <cmath>


double P5::abs(double value) {
    return std::abs(value);
}

double P5::ceil(double value) {
    return std::ceil(value);
}

double P5::constrain(double value, double min, double max) {
    return std::fmin(std::fmax(value, min), max);
}

double P5::dist(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

double P5::exp(double value) {
    return std::exp(value);
}

double P5::floor(double value) {
    return std::floor(value);
}

double P5::lerp(double start, double stop, double amt) {
    return start + (stop - start) * amt;
}

double P5::log(double value) {
    return std::log(value);
}

double P5::mag(double a, double b) {
    return std::sqrt(a * a + b * b);
}

double P5::map(double value, double start1, double stop1, double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

double P5::max(double a, double b) {
    return std::fmax(a, b);
}

double P5::max(std::vector<double> values) {
    double max = values[0];
    for (int i = 1; i < values.size(); i++) {
        max = std::fmax(max, values[i]);
    }
    return max;
}

double P5::min(double a, double b) {
    return std::fmin(a, b);
}

double P5::min(std::vector<double> values) {
    double min = values[0];
    for (int i = 1; i < values.size(); i++) {
        min = std::fmin(min, values[i]);
    }
    return min;
}

double P5::norm(double value, double start, double stop) {
    return (value - start) / (stop - start);
}

double P5::pow(double value, double exponent) {
    return std::pow(value, exponent);
}

double P5::round(double value) {
    return std::round(value);
}

double P5::sq(double value) {
    return value * value;
}

double P5::sqrt(double value) {
    return std::sqrt(value);
}

double P5::fract(double value) {
    return value - std::floor(value);
}