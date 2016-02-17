#include "Color.h"

Color::Color() {
    this->r = 255;
    this->g = 255;
    this->b = 255;
}

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const Color& c) {
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
}
