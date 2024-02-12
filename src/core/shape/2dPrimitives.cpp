#include "../main.hpp"
#include <cmath>
#include <iostream>

/**
 * This function does 3 things:
 *
 *   1. Bounds the desired start/stop angles for an arc (in radians) so that:
 *
 *          0 <= start < TWO_PI ;    start <= stop < start + TWO_PI
 *
 *      This means that the arc rendering functions don't have to be concerned
 *      with what happens if stop is smaller than start, or if the arc 'goes
 *      round more than once', etc.: they can just start at start and increase
 *      until stop and the correct arc will be drawn.
 *
 *   2. Optionally adjusts the angles within each quadrant to counter the naive
 *      scaling of the underlying ellipse up from the unit circle.  Without
 *      this, the angles become arbitrary when width != height: 45 degrees
 *      might be drawn at 5 degrees on a 'wide' ellipse, or at 85 degrees on
 *      a 'tall' ellipse.
 *
 *   3. Flags up when start and stop correspond to the same place on the
 *      underlying ellipse.  This is useful if you want to do something special
 *      there (like rendering a whole ellipse instead).
 */
void normalizeArcAngles(double &start, double &stop, float width, float height, bool correctForScaling, bool &correspondToSamePoint){
    const double eplsilon = 0.00001;
    double separation;

    start = start - (TWO_PI * std::floor(start / TWO_PI));

    stop = stop - (TWO_PI * std::floor(stop / TWO_PI));
    

    double diff = std::abs(start - stop);

    separation = std::min(diff, TWO_PI - diff);

    if (correctForScaling) {
        if (start <= HALF_PI) {
            start = atan(width / height * tan(start));
        } else if (start > HALF_PI && start <= 3 * HALF_PI) {
            start = atan(width / height * tan(start)) + PI;
        } else {
            start = atan(width / height * tan(start)) + TWO_PI;
        }
        if (stop <= HALF_PI) {
            stop = atan(width / height * tan(stop));
        } else if (stop > HALF_PI && stop <= 3 * HALF_PI) {
            stop = atan(width / height * tan(stop)) + PI;
        } else {
            stop = atan(width / height * tan(stop)) + TWO_PI;
        }
    }

    if(start > stop){
        stop += TWO_PI;
    }

    correspondToSamePoint = (separation < eplsilon);
}

void modeAdjust(float &x, float &y, float &w, float &h, std::string mode){
    if (mode == CORNER) {
        return;
    } else if (mode == CORNERS) {
        w = w - x;
        h = h - y;
    } else if (mode == RADIUS) {
        x = x - w;
        y = y - h;
        w = 2 * w;
        h = 2 * h;
    } else if (mode == CENTER) {
        x = x - w * 0.5f;
        y = y - h * 0.5f;
    }
}

void P5::arc(float x, float y, float w, float h, double start, double stop, ArcMode mode){
    if(!this->_isParametersValid("arc", {x, y, w, h, (float)start, (float)stop})){
        return;
    }

    if(!this->_renderer->getDoStroke() && !this->_renderer->getDoFill()){
        return;
    }

    if(start == stop){
        return;
    }

    start = this->_toRadians(start);
    stop = this->_toRadians(stop);

    w = std::abs(w);
    h = std::abs(h);

    modeAdjust(x, y, w, h, this->_renderer->getEllipseMode());

    bool correspondToSamePoint;
    normalizeArcAngles(start, stop, w, h, true, correspondToSamePoint);

    if(correspondToSamePoint){
        this->_renderer->_ellipse(x, y, w, h);
    }else{
        this->_renderer->_arc(x, y, w, h, start, stop, mode, this->_window);
    }
}