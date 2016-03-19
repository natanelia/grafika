#include "Color.h"

Color::Color() {
    this->r = 255;
    this->g = 255;
    this->b = 255;
}

Color::Color(std::string strHex) {
    this->r = strtol(strHex.substr(0, 2).c_str(), NULL, 16);
    this->g = strtol(strHex.substr(2, 2).c_str(), NULL, 16);
    this->b = strtol(strHex.substr(4, 2).c_str(), NULL, 16);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const Color& c) {
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
}
