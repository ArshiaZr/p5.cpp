#ifndef P5_CONSTANTS_HPP
#define P5_CONSTANTS_HPP

#include <string>
#include <unordered_map>
#include <variant>

// Include necessary headers here

// Constants
#define PI 3.14159265358979323846
#define HALF_PI PI / 2
// ... other constants ...

// Enums
// GRAPHICS
enum GlMode {
    P2D, // default
    WEBGL,
    WEBGL2
};

// ENVIRONMENT
enum CursorType {
    ARROW, // default
    CROSS,
    HAND,
    MOVE,
    TEXT,
    WAIT
};

enum AngleMode{
    DEGREES, // default
    RADIANS
};

// SHAPE
// enum RectMode{
//     CORNER, // default
//     CORNERS,
//     CENTER,
//     RADIUS
// };

// enum EllipseMode{
//     CENTER,
//     CORNER, // default
//     CORNERS,
//     RADIUS
// };

#define CORNER "corner" // ShapeMode
#define CORNERS "corners" // ShapeMode
#define CENTER "center" // ShapeMode and HorizontalAlign and VerticalAlign
#define RADIUS "radius" 
#define LEFT "left" // HorizontalAlign
#define RIGHT "right" // HorizontalAlign
#define TOP "top" // VerticalAlign
#define BOTTOM "bottom" // VerticalAlign
#define BASELINE "baseline" // VerticalAlign

enum BeginShapeMode {
    POINTS, // default
    LINES,
    TRIANGLES,
    TRIANGLE_FAN,
    TRIANGLE_STRIP,
    QUADS,
    QUAD_STRIP,
    TESS
};

#define CLOSE "close"

enum ArcMode {
    CHORD, // default
    PIE,
    OPEN
};

// COLOR 
enum ColorMode {
    RGB, // default
    HSB,
    HSL
};

// INPUT
#define ALT 18
#define BACKSPACE 8
#define CONTROL 17
#define DELETE 46
#define DOWN_ARROW 40
#define ENTER 13
#define ESCAPE 27
#define LEFT_ARROW 37
#define OPTION 18
#define RETURN 13
#define RIGHT_ARROW 39
#define SHIFT 16
#define TAB 9
#define UP_ARROW 38

// RENDERING
enum BlendMode {
    BLEND, // default
    REMOVE,
    ADD,
    SUBTRACT,
    DARKEST,
    LIGHTEST,
    DIFFERENCE,
    EXCLUSION,
    MULTIPLY,
    SCREEN,
    REPLACE,
    OVERLAY,
    HARD_LIGHT,
    SOFT_LIGHT,
    DODGE,
    BURN
};

// FILTERS
enum FilterType {
    THRESHOLD,
    GRAY,
    OPAQUE,
    INVERT,
    POSTERIZE,
    BLUR,
    ERODE,
    DILATE
};

using ContextValues = std::variant<bool, double, unsigned int, std::string, ColorMode>;

#endif // P5_CONSTANTS_HPP