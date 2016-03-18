#include "Color.h"

Color::Color() {
    this->r = 255;
    this->g = 255;
    this->b = 255;
}

Color::Color(std::string hex) {
    std::stringstream ss;
    std::string r = hex.substr(0, 2);
    std::string g = hex.substr(2, 2);
    std::string b = hex.substr(4, 2);
    ss << std::hex << r;
    ss >> this->r;
    ss.str("");
    ss.clear();
    ss << std::hex << g;
    ss >> this->g;
    ss.str("");
    ss.clear();
    ss << std::hex << b;
    ss >> this->b;
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
