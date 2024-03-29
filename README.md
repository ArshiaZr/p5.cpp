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

3. Link your program with the `p5.cpp` library:

   ```bash
   g++ your_program.cpp -o your_program -I/the/include/path -I/SFML/include/path -l/SFML/libs -L/p5/static/library -lp5
   ```

You can also use this [p5_cpp_starter](https://github.com/ArshiaZr/p5_cpp_starter) repository as a starter template for using p5.cpp in your C++ projects.(Recommended)

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
#include <iostream>
#include "p5.hpp"


// Create a new instance of the P5 class
P5& p5 = P5::getInstance();

// Define the setup and draw functions
void setup(){
    p5.createCanvas(400, 400);
}

// Define the setup and draw functions
void draw(){
    p5.background(220);
    p5.fill(255);
    p5.ellipse(200, 200, 100, 100);
}

// Main function
int main(){
    // Register the setup and draw functions
    p5.registerMethod("setup", setup);
    p5.registerMethod("draw", draw);

    // Run the sketch
    p5.run();

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
