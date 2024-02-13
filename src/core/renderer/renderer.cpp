#include "renderer.hpp"
#include <iostream>
#include <cmath>
#include <vector>

// Constructor
Renderer::Renderer(){
    // this->_clipping = false;
    // this->_clipInvert = false;

    this->_rectMode = CORNER;
    this->_curveTightness = 0.f;
    this->_colorMode = ColorMode::RGB;
    this->_context = std::stack<std::unordered_map<std::string, ContextValues>>();

    this->_ellipseMode = CENTER;
    this->_doStroke = true;
    this->_strokeColor = Color(0, 0, 0, 255);
    this->_strokeWeight = 1.0f;
    this->_doFill = true;
    this->_fillColor = Color(255, 255, 255, 255);
}

// Helper functions
std::vector<float> acuteArcToBezier(double start, double size){
    // Evaluate constants.
    float alpha = size / 2.0f;
    float cos_alpha = std::cos(alpha);
    float sin_alpha = std::sin(alpha);
    float cot_alpha = 1.0f / std::tan(alpha);
    // This is how far the arc needs to be rotated.
    float phi = start + alpha;
    float cos_phi = std::cos(phi);
    float sin_phi = std::sin(phi);
    float lambda = (4.0f - cos_alpha) / 3.0f;
    float mu = sin_alpha + (cos_alpha - lambda) * cot_alpha;

    return {
        std::cos((float)start), 
        std::sin((float)start),
        lambda * cos_phi + mu * sin_phi,
        lambda * sin_phi - mu * cos_phi,
        lambda * cos_phi - mu * sin_phi,
        lambda * sin_phi + mu * cos_phi,
        std::cos((float)(start + size)),
        std::sin((float)(start + size))
    };
}

std::vector<sf::Vector2f> bezierCurveTo(float startx, float starty, float cp1x, float cp1y, float cp2x, float cp2y, float x, float y) {
    // Set up the Bézier curve points
    sf::Vector2f startPoint = sf::Vector2f(startx, starty); // Get the current end point

    std::vector<sf::Vector2f> points;
    float t = 0.0f;

    // Increment t from 0 to 1 with a small step size
    while (t <= 1.0f) {
        // Calculate the position of the point on the Bézier curve using the formula
        // B(t) = (1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3, where P0, P1, P2, and P3 are control points
        float one_minus_t = 1.0f - t;
        float tt = t * t;
        float ttt = tt * t;

        sf::Vector2f point =
            (one_minus_t * one_minus_t * one_minus_t) * startPoint +
            (3.0f * (one_minus_t * one_minus_t ) * t) * sf::Vector2f(cp1x, cp1y) +
            (3.0f * one_minus_t * tt) * sf::Vector2f(cp2x, cp2y) +
            (ttt) * sf::Vector2f(x, y);

        points.push_back(point);

        t += 0.01f; // Adjust this step size as needed for smoother or coarser curves
    }

    // Draw the Bézier curve
    return points;
}

std::vector<std::vector<sf::Vector2f>> getPointsInCurves(float x, float y, float w, float h, double start, double stop){
    std::vector<std::vector<sf::Vector2f>> allPoints;
    
    double rx = w / 2.0f;
    double ry = h / 2.0f;
    const double eplsilon = 0.00001f;

    double curArc = 0;
    std::vector<std::vector<float>> curves;

    x += rx;
    y += ry;

    while(stop - start >= eplsilon){
        curArc = std::min((float)(stop - start), (float)HALF_PI);
        curves.push_back(acuteArcToBezier(start, curArc));
        start += curArc;
    }


    for (int i = 0; i < curves.size(); i++){
        std::vector<float> curve = curves[i];
        std::vector<sf::Vector2f> points = 
            bezierCurveTo(x + curve[0] * rx, y + curve[1] * ry, x + curve[2] * rx,
                    y + curve[3] * ry, x + curve[4] * rx, y + curve[5] * ry,
                    x + curve[6] * rx, y + curve[7] * ry);
        allPoints.push_back(points);
    }

    return allPoints;
}

// Public API functions
void Renderer::push(){
    this->_context.push({
        // {"clipping", this->_clipping},
        // {"clipInvert", this->_clipInvert},
        {"curveTightness", this->_curveTightness},
        {"colorMode", this->_colorMode},
        {"ellipseMode", this->_ellipseMode},
        {"rectMode", this->_rectMode},
        {"doStroke", this->_doStroke},
        {"doFill", this->_doFill},
        {"fillColor", this->_fillColor},
        {"strokeColor", this->_strokeColor},
        {"strokeWeight", this->_strokeWeight}

    });
}

void Renderer::pop(){
    if(this->_context.size() > 0){
        std::unordered_map<std::string, ContextValues> context = this->_context.top();
        this->_context.pop();
        // this->_clipping = std::get<bool>(context["clipping"]);
        // this->_clipInvert = std::get<bool>(context["clipInvert"]);
        this->_rectMode = std::get<std::string>(context["rectMode"]);
        this->_curveTightness = std::get<double>(context["curveTightness"]);
        this->_colorMode = std::get<ColorMode>(context["colorMode"]);
        this->_ellipseMode = std::get<std::string>(context["ellipseMode"]);
        this->_doStroke = std::get<bool>(context["doStroke"]);
        this->_strokeColor = std::get<Color>(context["strokeColor"]);
        this->_doFill = std::get<bool>(context["doFill"]);
        this->_fillColor = std::get<Color>(context["fillColor"]);
        this->_strokeWeight = std::get<double>(context["strokeWeight"]);
    }else{
        std::cout << "Error: No context to pop" << std::endl;
    }
}

bool Renderer::getDoStroke(){
    return std::get<bool>(this->_doStroke);
}

void Renderer::setDoStroke(bool val){
    this->_doStroke = val;
}

void Renderer::setStrokeColor(Color color){
    this->_strokeColor = color;
}

double Renderer::getStrokeWeight(){
    return std::get<double>(this->_strokeWeight);
}

void Renderer::setStrokeWeight(double weight){
    this->_strokeWeight = weight;
}

bool Renderer::getDoFill(){
    return std::get<bool>(this->_doFill);
}

void Renderer::setDoFill(bool val){
    this->_doFill = val;
}

void Renderer::setFillColor(Color color){
    this->_fillColor = color;
}

std::string Renderer::getEllipseMode(){
    return std::get<std::string>(this->_ellipseMode);
}

void Renderer::setEllipseMode(std::string mode){
    this->_ellipseMode = mode;
}

std::string Renderer::getRectMode(){
    return std::get<std::string>(this->_rectMode);
}

void Renderer::setRectMode(std::string mode){
    this->_rectMode = mode;
}

void Renderer::setColorMode(ColorMode mode){
    this->_colorMode = mode;
}

void Renderer::_arc(float x, float y, float w, float h, double start, double stop, ArcMode mode, sf::RenderWindow &window){
    std::vector<std::vector<sf::Vector2f>> allPoints = getPointsInCurves(x, y, w, h, start, stop);

    double strokeWeight = std::get<double>(this->_strokeWeight);
    sf::ConvexShape arcToDraw;
    arcToDraw.setPointCount(0); 

    if(std::get<bool>(this->_doFill)){
        // std::cout << "Drawing fill" << std::endl;
        arcToDraw.setFillColor(std::get<Color>(this->_fillColor));
        if(mode != ArcMode::OPEN && std::get<bool>(this->_doStroke)){
            arcToDraw.setOutlineColor(std::get<Color>(this->_strokeColor));
            arcToDraw.setOutlineThickness(strokeWeight);
        }

        for(int i = 0; i < allPoints.size(); i++){
            // each curve
            for(int j = 0; j < allPoints[i].size(); j++){
                // fill
                arcToDraw.setPointCount(arcToDraw.getPointCount() + 1);
                arcToDraw.setPoint(arcToDraw.getPointCount() - 1, allPoints[i][j]);
            }
        }
        if(mode == ArcMode::PIE){
            arcToDraw.setPointCount(arcToDraw.getPointCount() + 1);
            arcToDraw.setPoint(arcToDraw.getPointCount() - 1, sf::Vector2f(x + w / 2.0f , y + h / 2.0f));
        }
        window.draw(arcToDraw);
    }

    if(std::get<bool>(this->_doStroke)){  
        for(int i = 0; i < allPoints.size(); i++){
            // each curve
            for(int j = 1; j < allPoints[i].size(); j++){
                // stroke
                this->_line(allPoints[i][j-1].x, allPoints[i][j-1].y, allPoints[i][j].x, allPoints[i][j].y, window);
            }
            if(i == allPoints.size() - 1){
                if(mode == ArcMode::CHORD){
                    this->_line(allPoints[i][allPoints[i].size() - 1].x, allPoints[i][allPoints[i].size() - 1].y, allPoints[0][0].x, allPoints[0][0].y, window);
                }else if(mode == ArcMode::PIE){
                    this->_line(allPoints[i][allPoints[i].size() - 1].x, allPoints[i][allPoints[i].size() - 1].y, x + w / 2.0f, y + h / 2.0f , window);
                    this->_line(x + w / 2.0f, y + h / 2.0f, allPoints[0][0].x, allPoints[0][0].y, window);
                }
            }
        }
    }
    
}

void Renderer::_ellipse(float x, float y, float w, float h, sf::RenderWindow &window){
    float centerX = x + w / 2.0f;
    float centerY = y + h / 2.0f;
    float radiusX = w / 2.0f;
    float radiusY = h / 2.0f;

    sf::CircleShape ellipse;

    ellipse.setRadius(radiusX);
    ellipse.setScale(1, radiusY / radiusX);
    ellipse.setOrigin(ellipse.getRadius(), ellipse.getRadius()); // Set origin to center
    ellipse.setPosition(centerX, centerY);

   
    if(std::get<bool>(this->_doFill)){
        ellipse.setFillColor(std::get<Color>(this->_fillColor));
    }else{
        ellipse.setFillColor(sf::Color::Transparent);
    }

    if(std::get<bool>(this->_doStroke)){
        ellipse.setOutlineThickness(std::get<double>(this->_strokeWeight));
        ellipse.setOutlineColor(std::get<Color>(this->_strokeColor));
    }
    
    window.draw(ellipse);
}

void Renderer::_line(float x1, float y1, float x2, float y2, sf::RenderWindow &window){
    double strokeWeight = std::get<double>(this->_strokeWeight);
    Color lineColor = std::get<Color>(this->_strokeColor);

    sf::Vector2f direction(x2 - x1, y2 - y1);

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    direction /= length;

    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;

    sf::RectangleShape line(sf::Vector2f(length, strokeWeight));
    line.setFillColor(lineColor);
    line.setOrigin(0, strokeWeight / 2.0f);
    line.setPosition(x1, y1);
    line.setRotation(angle);

    window.draw(line);    
}

void Renderer::_point(float x, float y, sf::RenderWindow &window){
    sf::CircleShape point;
    point.setRadius((float)std::get<double>(this->_strokeWeight) / 2.0f);
    point.setOrigin(point.getRadius(), point.getRadius());
    point.setPosition(x, y);
    point.setFillColor(std::get<Color>(this->_strokeColor));
    window.draw(point);
}

void Renderer::_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, sf::RenderWindow &window){
    sf::ConvexShape quad;
    quad.setPointCount(4);
    quad.setPoint(0, sf::Vector2f(x1, y1));
    quad.setPoint(1, sf::Vector2f(x2, y2));
    quad.setPoint(2, sf::Vector2f(x3, y3));
    quad.setPoint(3, sf::Vector2f(x4, y4));

    if(std::get<bool>(this->_doFill)){
        quad.setFillColor(std::get<Color>(this->_fillColor));
    }else{
        quad.setFillColor(sf::Color::Transparent);
    }

    if(std::get<bool>(this->_doStroke)){
        quad.setOutlineThickness(std::get<double>(this->_strokeWeight));
        quad.setOutlineColor(std::get<Color>(this->_strokeColor));
    }

    window.draw(quad);
}

void Renderer::_rect(float x, float y, float w, float h, float tl, float tr, float br, float bl, sf::RenderWindow &window){
    sf::ConvexShape rect;

    if(std::get<bool>(this->_doFill)){
        rect.setFillColor(std::get<Color>(this->_fillColor));
    }else{
        rect.setFillColor(sf::Color::Transparent);
    }

    if(std::get<bool>(this->_doStroke)){
        rect.setOutlineThickness(std::get<double>(this->_strokeWeight));
        rect.setOutlineColor(std::get<Color>(this->_strokeColor));
    }

    rect.setPointCount(0);

    if(tl > 0){
        std::vector<sf::Vector2f> points1 = getPointsInCurves(x, y, tl * 2, tl * 2, PI, PI + HALF_PI)[0];
        for(int i = 0; i < points1.size(); i++){
            rect.setPointCount(rect.getPointCount() + 1);
            rect.setPoint(rect.getPointCount() - 1, points1[i]);
        }
    }else{
        rect.setPointCount(rect.getPointCount() + 1);
        rect.setPoint(rect.getPointCount() - 1, sf::Vector2f(x, y));
    }

    if(tr > 0){
        std::vector<sf::Vector2f> points2 = getPointsInCurves(x + w - tr * 2, y, tr * 2, tr * 2, PI + HALF_PI, TWO_PI)[0];
        for(int i = 0; i < points2.size(); i++){
            rect.setPointCount(rect.getPointCount() + 1);
            rect.setPoint(rect.getPointCount() - 1, points2[i]);
        }
    }else{
        rect.setPointCount(rect.getPointCount() + 1);
        rect.setPoint(rect.getPointCount() - 1, sf::Vector2f(x + w, y));
    }
    if(br > 0){
        std::vector<sf::Vector2f> points3 = getPointsInCurves(x + w - br * 2, y + h - br * 2, br * 2, br * 2, 0, HALF_PI)[0];
        for(int i = 0; i < points3.size(); i++){
            rect.setPointCount(rect.getPointCount() + 1);
            rect.setPoint(rect.getPointCount() - 1, points3[i]);
        }
    }else{
        rect.setPointCount(rect.getPointCount() + 1);
        rect.setPoint(rect.getPointCount() - 1, sf::Vector2f(x + w, y + h));
    }

    if(bl > 0){
        std::vector<sf::Vector2f> points4 = getPointsInCurves(x, y + h - bl * 2, bl * 2, bl * 2, HALF_PI, PI)[0];
        for(int i = 0; i < points4.size(); i++){
            rect.setPointCount(rect.getPointCount() + 1);
            rect.setPoint(rect.getPointCount() - 1, points4[i]);
        }
    }else{
        rect.setPointCount(rect.getPointCount() + 1);
        rect.setPoint(rect.getPointCount() - 1, sf::Vector2f(x, y + h));
    }

    window.draw(rect);
}

void Renderer::_triangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::RenderWindow &window){
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(x1, y1));
    triangle.setPoint(1, sf::Vector2f(x2, y2));
    triangle.setPoint(2, sf::Vector2f(x3, y3));

    if(std::get<bool>(this->_doFill)){
        triangle.setFillColor(std::get<Color>(this->_fillColor));
    }else{
        triangle.setFillColor(sf::Color::Transparent);
    }

    if(std::get<bool>(this->_doStroke)){
        triangle.setOutlineThickness(std::get<double>(this->_strokeWeight));
        triangle.setOutlineColor(std::get<Color>(this->_strokeColor));
    }

    window.draw(triangle);
}

ColorMode Renderer::getColorMode(){
    return std::get<ColorMode>(this->_colorMode);
}