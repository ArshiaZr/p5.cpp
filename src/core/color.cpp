#include "main.hpp"
#include <math.h>
#include <iostream>


// Helper functions
float lerp(float start, float stop, double amt){
    return start + (stop - start) * amt;
}

// Public functions
void P5::colorMode(ColorMode mode){
    this->_colorMode = mode;
}

unsigned int P5::alpha(Color color){
    return color.a;
}

unsigned int P5::blue(Color color){
    return color.b;
}

unsigned int P5::brightness(Color color){
    float rLinear = color.r / 255.0f;
    float gLinear = color.g / 255.0f;
    float bLinear = color.b / 255.0f;

    // Calculate brightness using weighted sum of RGB components
    float b = 0.2126f * rLinear + 0.7152f * gLinear + 0.0722f * bLinear;

    // Scale brightness based on alpha value
    return b * (color.a / 255.0f);
}

Color P5::color(unsigned int gray){
    return color(gray, 255);
}

Color P5::color(unsigned int gray, unsigned int alpha){
    return color(gray, gray, gray, alpha);
}

Color P5::color(unsigned int v1, unsigned int v2, unsigned int v3){
    return color(v1, v2, v3, 255);
}

Color P5::color(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int alpha){
    std::vector<float> rgba = this->_parseColorInputs(v1, v2, v3, alpha);
    return Color(rgba[0], rgba[1], rgba[2], rgba[3]);
}

unsigned int P5::green(Color color){
    return color.g;
}

unsigned int P5::hue(Color color){
    float rLinear = color.r / 255.0f;
    float gLinear = color.g / 255.0f;
    float bLinear = color.b / 255.0f;

    float max = std::max(rLinear, std::max(gLinear, bLinear));
    float min = std::min(rLinear, std::min(gLinear, bLinear));

    float h = 0.0f;

    if (max == min){
        h = 0.0f;
    } else if (max == rLinear){
        h = (60.0f * (gLinear - bLinear) / (max - min) + 360.0f);
    } else if (max == gLinear){
        h = (60.0f * (bLinear - rLinear) / (max - min) + 120.0f);
    } else if (max == bLinear){
        h = (60.0f * (rLinear - gLinear) / (max - min) + 240.0f);
    }

    return (unsigned int)h;
}

Color P5::lerpColor(Color c1, Color c2, double amt){
    unsigned int r = (unsigned int)lerp(c1.r, c2.r, amt);
    unsigned int g = (unsigned int)lerp(c1.g, c2.g, amt);
    unsigned int b = (unsigned int)lerp(c1.b, c2.b, amt);
    unsigned int a = (unsigned int)lerp(c1.a, c2.a, amt);
    return color(r, g, b, a);

}

unsigned int P5::lightness(Color color){
    float rLinear = color.r / 255.0f;
    float gLinear = color.g / 255.0f;
    float bLinear = color.b / 255.0f;

    // Calculate lightness using weighted sum of RGB components
    float l = 0.2126f * rLinear + 0.7152f * gLinear + 0.0722f * bLinear;

    // Scale lightness based on alpha value
    return l * (color.a / 255.0f);

}

unsigned int P5::red(Color color){
    return color.r;
}

unsigned int P5::saturation(Color color){
    float rLinear = color.r / 255.0f;
    float gLinear = color.g / 255.0f;
    float bLinear = color.b / 255.0f;

    float max = std::max(rLinear, std::max(gLinear, bLinear));
    float min = std::min(rLinear, std::min(gLinear, bLinear));

    float s = 0.0f;

    if (max == min){
        s = 0.0f;
    } else {
        float l = (max + min) / 2.0f;
        if (l <= 0.5f){
            s = (max - min) / (max + min);
        } else {
            s = (max - min) / (2.0f - max - min);
        }
    }

    return (unsigned int)s;
}

void P5::printColor(Color c){
    std::cout << "r: " << this->red(c) << " g: " << this->green(c) << " b: " << this->blue(c) << " a: " << this->alpha(c) << std::endl;
}


// Private functions
std::vector<float> P5::_parseColorInputs(unsigned int r, unsigned int g, unsigned int b){
    return this->_parseColorInputs(r, g, b, 255);
}

std::vector<float> P5::_parseColorInputs(unsigned int r, unsigned int g, unsigned int b, unsigned int a){
    unsigned int maxes[4];
    maxes[0] = this->_colorMaxes[(int)this->_colorMode][0];
    maxes[1] = this->_colorMaxes[(int)this->_colorMode][1];
    maxes[2] = this->_colorMaxes[(int)this->_colorMode][2];
    maxes[3] = this->_colorMaxes[(int)this->_colorMode][3];
    std::vector<float> results(4, 0);
    results[0] = (float)r / maxes[0];
    results[1] = (float)g / maxes[1];
    results[2] = (float)b / maxes[2];
    results[3] = (float)a / maxes[3];

    for (int i = 0; i < 4; i++){
        results[i] = fminf(fmaxf(results[i], 0), 1);
    }

    if(this->_colorMode == ColorMode::HSB){
        return this->_colorFromHSB(results);
    } else if(this->_colorMode == ColorMode::HSL){
        return this->_colorFromHSL(results);
    }else{
        return {results[0] * 255, results[1] * 255, results[2] * 255, results[3] * 255};
    }
}

std::vector<float> P5::_colorFromHSB(std::vector<float> hsba) {
    float hue = hsba[0] * 6; // We will split hue into 6 sectors.
    float sat = hsba[1];
    float val = hsba[2];

    std::vector<float> RGBA(4);

    if (sat == 0) {
        RGBA = { val, val, val, hsba[3] }; // Return early if grayscale.
    } else {
        int sector = std::floor(hue);
        float tint1 = val * (1 - sat);
        float tint2 = val * (1 - sat * (hue - sector));
        float tint3 = val * (1 - sat * (1 + sector - hue));
        float red, green, blue;
        if (sector == 1) {
            // Yellow to green.
            red = tint2;
            green = val;
            blue = tint1;
        } else if (sector == 2) {
            // Green to cyan.
            red = tint1;
            green = val;
            blue = tint3;
        } else if (sector == 3) {
            // Cyan to blue.
            red = tint1;
            green = tint2;
            blue = val;
        } else if (sector == 4) {
            // Blue to magenta.
            red = tint3;
            green = tint1;
            blue = val;
        } else if (sector == 5) {
            // Magenta to red.
            red = val;
            green = tint1;
            blue = tint2;
        } else {
            // Red to yellow (sector could be 0 or 6).
            red = val;
            green = tint3;
            blue = tint1;
        }
        RGBA = { red , green, blue, hsba[3] };
    }
    RGBA[0] = RGBA[0] * 255;
    RGBA[1] = RGBA[1] * 255;
    RGBA[2] = RGBA[2] * 255;
    RGBA[3] = RGBA[3] * 255;
    return RGBA;
}

std::vector<float> P5::_colorFromHSL(std::vector<float> hsla) {
    float hue = hsla[0] * 6; // We will split hue into 6 sectors.
    float sat = hsla[1];
    float li = hsla[2];

    std::vector<float> RGBA;

    if (sat == 0) {
        RGBA = { li, li, li, hsla[3] }; // Return early if grayscale.
    } else {
        // Calculate brightness.
        float val;
        if (li < 0.5) {
            val = (1 + sat) * li;
        } else {
            val = li + sat - li * sat;
        }

        // Define zest.
        float zest = 2 * li - val;

        // Implement projection (project onto green by default).
        auto hzvToRGB = [](float hue, float zest, float val) {
            if (hue < 0) {
                // Hue must wrap to allow projection onto red and blue.
                hue += 6;
            } else if (hue >= 6) {
                hue -= 6;
            }
            if (hue < 1) {
                // Red to yellow (increasing green).
                return zest + (val - zest) * hue;
            } else if (hue < 3) {
                // Yellow to cyan (greatest green).
                return val;
            } else if (hue < 4) {
                // Cyan to blue (decreasing green).
                return zest + (val - zest) * (4 - hue);
            } else {
                // Blue to red (least green).
                return zest;
            }
        };

        // Perform projections, offsetting hue as necessary.
        RGBA = {
            hzvToRGB(hue + 2, zest, val),
            hzvToRGB(hue, zest, val),
            hzvToRGB(hue - 2, zest, val),
            hsla[3]
        };
    }
    RGBA[0] = RGBA[0] * 255;
    RGBA[1] = RGBA[1] * 255;
    RGBA[2] = RGBA[2] * 255;
    RGBA[3] = RGBA[3] * 255;
    return RGBA;
}
