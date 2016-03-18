#ifndef __COLOR
#define __COLOR
#include <cstdio>
#include <cstring>
#include <sstream>

class Color {
public:
    int r;
    int g;
    int b;

    Color();
    Color(int r, int g, int b);
    Color(std::string hex);
    Color(const Color& c);

    int isEqual(Color& c) {
        return (r == c.r && g == c.g && b == c.b);
    }

    void print() {
        printf("r:%d g:%d b:%d\n", r, g, b);
    }
};

#endif