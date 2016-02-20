#ifndef __SHADOWBUFFER
#define __SHADOWBUFFER

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "Color.h"

using namespace std;

class ShadowBuffer {
public:
    Color backgroundColor;
    int lineLength;
    int width;
    int height;
    int offsetX;
    int offsetY;
    int bufferSize;
    char *sfbp;
    vector<ShadowBuffer *> shadows;

    ShadowBuffer(int width, int height, int offsetX, int offsetY, int lineLength);

    void plot(int x, int y, Color& c);
    Color * getColor(int x, int y);
    void draw();
    void clear();

};

#endif