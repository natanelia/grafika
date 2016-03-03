#ifndef __COLOR
#define __COLOR

class Color {
public:
    int r;
    int g;
    int b;

    Color();
    Color(int r, int g, int b);
    Color(const Color& c);

    int isEqual(Color& c) {
        return (r == c.r && g == c.g && b == c.b);
    }
};

#endif