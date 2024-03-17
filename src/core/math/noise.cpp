// File: noise.cpp
#include "../main.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>

double P5::noiseSeed(unsigned int seed) {
    this->_noiseGenerator.seed(seed);
    // Initialize permutation table
    std::iota(this->_permutation.begin(), this->_permutation.end(), 0);
    std::shuffle(this->_permutation.begin(), this->_permutation.end(), this->_noiseGenerator);
    this->_permutation.insert(this->_permutation.end(), this->_permutation.begin(),this->_permutation.end());
}

double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double a, double b, double t) {
    return a + t * (b - a);
}

double grad(int hash, double x, double y, double z) {
    int h = hash & 15; // Convert low 4 bits of hash code into 12 gradient directions
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double P5::noise(double x, double y, double z) {
    // Determine grid cell coordinates
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    // Relative position within grid cell
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    // Compute fade curves for x, y, z
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // Hash coordinates of the 8 cube corners
    int A  = this->_permutation[X] + Y;
    int AA = this->_permutation[A] + Z;
    int AB = this->_permutation[A + 1] + Z;
    int B  = this->_permutation[X + 1] + Y;
    int BA = this->_permutation[B] + Z;
    int BB = this->_permutation[B + 1] + Z;


    // Interpolate along x the contributions from each of the 8 corners
    double x1 = lerp(grad(this->_permutation[AA], x, y, z), grad(this->_permutation[BA], x - 1, y, z), u);
    double x2 = lerp(grad(this->_permutation[AB], x, y - 1, z), grad(this->_permutation[BB], x - 1, y - 1, z), u);
    double y1 = lerp(x1, x2, v);

    // Interpolate along y
    double x3 = lerp(grad(this->_permutation[AA + 1], x, y, z - 1), grad(this->_permutation[BA + 1], x - 1, y, z - 1), u);
    double x4 = lerp(grad(this->_permutation[AB + 1], x, y - 1, z - 1), grad(this->_permutation[BB + 1], x - 1, y - 1, z - 1), u);
    double y2 = lerp(x3, x4, v);

    // Interpolate along z
    return (lerp(y1, y2, w) + 1.0) / 2.0; // Normalize to [0, 1]
}

double P5::noise(double x, double y) {
    return noise(x, y, 0);
}

double P5::noise(double x) {
    return noise(x, 0, 0);
}
