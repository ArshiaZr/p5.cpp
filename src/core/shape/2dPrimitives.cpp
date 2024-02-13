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
        if(w < 0){
            x = x + w;
            w = -w;
        }
        if(h < 0){
            y = y + h;
            h = -h;
        }
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
        this->_renderer->_ellipse(x, y, w, h, this->_window);
    }else{
        this->_renderer->_arc(x, y, w, h, start, stop, mode, this->_window);
    }
}

void P5::ellipse(float x, float y, float w, float h){
    if(!this->_isParametersValid("ellipse", {x, y, w, h})){
        return;
    }

    if(!this->_renderer->getDoStroke() && !this->_renderer->getDoFill()){
        return;
    }

    w = std::abs(w);
    h = std::abs(h);

    modeAdjust(x, y, w, h, this->_renderer->getEllipseMode());

    this->_renderer->_ellipse(x, y, w, h, this->_window);
}

void P5::circle(float x, float y, float d){
    this->ellipse(x, y, d, d);
}

void P5::line(float x1, float y1, float x2, float y2){
    if(!this->_isParametersValid("line", {x1, y1, x2, y2})){
        return;
    }

    if(!this->_renderer->getDoStroke()){
        return;
    }

    this->_renderer->_line(x1, y1, x2, y2, this->_window);
}

void P5::point(float x, float y){
    if(!this->_isParametersValid("point", {x, y})){
        return;
    }

    if(!this->_renderer->getDoStroke()){
        return;
    }

    this->_renderer->_point(x, y, this->_window);
}

void P5::point(Vector2f point){
    this->point(point.x, point.y);
}

void P5::quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    if(!this->_isParametersValid("quad", {x1, y1, x2, y2, x3, y3, x4, y4})){
        return;
    }

    if(!this->_renderer->getDoStroke() && !this->_renderer->getDoFill()){
        return;
    }

    this->_renderer->_quad(x1, y1, x2, y2, x3, y3, x4, y4, this->_window);
}

void P5::rect(float x, float y, float w, float h, float tl, float tr, float br, float bl){
    if(!this->_isParametersValid("rect", {x, y, w, h, tl, tr, br, bl})){
        return;
    }

    if(!this->_renderer->getDoStroke() && !this->_renderer->getDoFill()){
        return;
    }

    w = std::abs(w);
    h = std::abs(h);

    modeAdjust(x, y, w, h, this->_renderer->getRectMode());

    this->_renderer->_rect(x, y, w, h, tl, tr, br, bl, this->_window);
}

void P5::square(float x, float y, float s, float tl, float tr, float br, float bl){
    this->rect(x, y, s, s, tl, tr, br, bl);
}

void P5::triangle(float x1, float y1, float x2, float y2, float x3, float y3){
    if(!this->_isParametersValid("triangle", {x1, y1, x2, y2, x3, y3})){
        return;
    }

    if(!this->_renderer->getDoStroke() && !this->_renderer->getDoFill()){
        return;
    }

    this->_renderer->_triangle(x1, y1, x2, y2, x3, y3, this->_window);
}