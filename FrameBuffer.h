#ifndef __FRAMEBUFFER
#define __FRAMEBUFFER

#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Color.h"
#include "ShadowBuffer.h"

#define UNAVAILABLE_HEIGHT 15

using namespace std;

class FrameBuffer {
public:
    int width;
    int height;
    int screenSize;
    Color backgroundColor;

    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    char *fbp;

    FrameBuffer();

    void plot(int x, int y, Color& c);
    Color * getColor(int x, int y);
    void draw();
    void draw(ShadowBuffer& sb);
    void clear();

};

#endif