# p5.cpp: C++ Implementation of p5.js Library

## Introduction

p5.cpp is a project that aims to bring the functionalities of the popular p5.js library to the C++ programming language. The p5.js library is well-known for its simplicity and ease of use in creative coding and interactive graphics. This project attempts to provide a similar experience for C++ programmers who want to explore creative coding and graphics in a familiar environment in a faster way. This project is a study base project for me to get better and better in C++ programming language.

## Getting Started

To use p5.cpp in your C++ projects, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/ArshiaZr/p5.cpp.git
   ```

2. Include the `p5.cpp` header file in your C++ program:

   ```cpp
   #include "p5.hpp"
   ```

<!-- 3. Link your program with the `p5.c` library(or any other C compiler):

   ```bash
   gcc your_program.c -o your_program -lp5
   ``` -->

## Features

p5.cpp aims to replicate the core features of the p5.js library, including:

- Drawing basic shapes (rectangles, ellipses, lines, etc.).
- Handling user input (keyboard and mouse events).
- Animation and frame-based timing.
- Loading and displaying images.
- Basic 2D transformations (translate, rotate, scale).
- And more...

Refer to the [p5.js documentation](https://p5js.org/reference/) for a comprehensive list of features, as p5.c strives to mirror its functionality closely.

## Examples

```cpp
#include "p5.hpp"

P5 p;

void setup(){
    p.createCanvas(500, 500, WebglMode::P2D);
    p.frameRate(5);
    Color c = p.color(18, 42, 22, 200);
    p.printColor(c);

    p.colorMode(ColorMode::HSB);
    Color c1 = p.color(18, 42, 22, 200);
    p.printColor(c1);

    p.colorMode(ColorMode::HSL);
    Color c2 = p.color(18, 42, 22, 200);
    p.printColor(c2);
}

void draw(){
}

void windowResized(){
}

int main(){
    p.registerMethod("setup", setup);
    p.registerMethod("draw", draw);
    p.registerMethod("windowResized", windowResized);

    p.run();
    return 0;
}
```

## Documentation

Check the `docs` directory for the p5.cpp documentation, which provides detailed information on functions, syntax, and usage.

## Contributing

Feel free to contribute to p5.cpp by opening issues or submitting pull requests. Follow the guidelines in the `CONTRIBUTING.md` file.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Acknowledgments

- The p5.js community for inspiration.
- The contributors to the original p5.js library.

Happy coding with p5.cpp! 🚀
