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

std::vector<sf::Vector2f> bezierCurveTo(float startx, float starty, float cp1x, float cp1y, float cp2x, float cp2y, float x, float y, sf::RenderWindow& window) {
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

// Public API functions
void Renderer::push(){
    this->_context.push({
        // {"clipping", this->_clipping},
        // {"clipInvert", this->_clipInvert},
        {"rectMode", this->_rectMode},
        {"curveTightness", this->_curveTightness},
        {"colorMode", this->_colorMode},
        {"ellipseMode", this->_ellipseMode},
        {"doStroke", this->_doStroke},
        {"doFill", this->_doFill},
        {"fillColor", this->_fillColor},
        {"strokeColor", this->_strokeColor}

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

void Renderer::setColorMode(ColorMode mode){
    this->_colorMode = mode;
}

void Renderer::_arc(float x, float y, float w, float h, double start, double stop, ArcMode mode, sf::RenderWindow &window){
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

    sf::ConvexShape arcToDraw;
    arcToDraw.setPointCount(0); 

    if(std::get<bool>(this->_doFill)){
        arcToDraw.setFillColor(std::get<Color>(this->_fillColor));

        for (int i = 0; i < curves.size(); i++){
            std::vector<float> curve = curves[i];
            std::vector<sf::Vector2f> points = 
                bezierCurveTo(x + curve[0] * rx, y + curve[1] * ry, x + curve[2] * rx,
                        y + curve[3] * ry, x + curve[4] * rx, y + curve[5] * ry,
                        x + curve[6] * rx, y + curve[7] * ry, window);
        
            for(int j = 0; j < points.size(); j++){
                // fill
                arcToDraw.setPointCount(arcToDraw.getPointCount() + 1);
                arcToDraw.setPoint(arcToDraw.getPointCount() - 1, points[j]);
            }
        }

        if(mode == ArcMode::PIE){
            arcToDraw.setPointCount(arcToDraw.getPointCount() + 1);
            arcToDraw.setPoint(arcToDraw.getPointCount() - 1, sf::Vector2f(x , y));
        }

        window.draw(arcToDraw);
    }

    if(std::get<bool>(this->_doStroke)){
        for (int i = 0; i < curves.size(); i++){
            std::vector<float> curve = curves[i];
            std::vector<sf::Vector2f> points = 
                bezierCurveTo(x + curve[0] * rx, y + curve[1] * ry, x + curve[2] * rx,
                        y + curve[3] * ry, x + curve[4] * rx, y + curve[5] * ry,
                        x + curve[6] * rx, y + curve[7] * ry, window);
        
            sf::VertexArray eachStroke(sf::LineStrip);

            for(int j = 0; j < points.size(); j++){
                // stroke
                eachStroke.append(sf::Vertex(points[j], std::get<Color>(this->_strokeColor)));
            }

            if(i == curves.size() - 1){
                if(mode == ArcMode::CHORD){
                    eachStroke.append(sf::Vertex(sf::Vector2f(x + curves[0][0] * rx, y + curves[0][1] * ry), std::get<Color>(this->_strokeColor)));
                }else if(mode == ArcMode::PIE){
                    eachStroke.append(sf::Vertex(sf::Vector2f(x, y), std::get<Color>(this->_strokeColor)));
                    eachStroke.append(sf::Vertex(sf::Vector2f(x + curves[0][0] * rx, y + curves[0][1] * ry), std::get<Color>(this->_strokeColor)));
                }
            }

            window.draw(eachStroke);
        }
    }
}

void Renderer::_ellipse(float x, float y, float w, float h){

}

ColorMode Renderer::getColorMode(){
    return std::get<ColorMode>(this->_colorMode);
}