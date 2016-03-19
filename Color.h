#ifndef __COLOR
#define __COLOR
#include <cstdio>
#include <cstdlib>
#include <string>

class Color {
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color();
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(std::string strHex);
    Color(const Color& c);

    int isEqual(Color& c) {
        return (r == c.r && g == c.g && b == c.b);
    }

    void print() {
        printf("r:%d g:%d b:%d || 0x%.2X%.2X%.2X\n", r, g, b, r, g, b);
    }
};

#endif