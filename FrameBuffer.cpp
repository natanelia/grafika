#include "FrameBuffer.h"

using namespace std;

FrameBuffer::FrameBuffer() {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screenSize = 0;
    char *fbp = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
   // printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screenSize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screenSize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    //printf("The framebuffer device was mapped to memory successfully.\n");


    this->fbfd = fbfd;
    this->vinfo = vinfo;
    this->finfo = finfo;
    this->screenSize = screenSize;
    this->width = vinfo.xres;
    this->height = vinfo.yres;
    this->fbp = fbp;
}

/*void FrameBuffer::draw() {
    for (int i = 0; i < drawings.size(); ++i) {
        drawings[i]->draw();
    }
}*/

void FrameBuffer::draw(ShadowBuffer& sb) {
    for (int y = 0; y < sb.height - UNAVAILABLE_HEIGHT; y++) {
        for (int x = 0; x < sb.width; x++) {
            memcpy(fbp + ((x + sb.offsetX) * 4 + (y + sb.offsetY) * sb.lineLength), sb.sfbp + ((x * 4 + y * sb.lineLength) % sb.bufferSize), 4);
        }
    }
}

void FrameBuffer::clear() {
    for (int y = 0; y < vinfo.yres - UNAVAILABLE_HEIGHT; ++y) {
        for (int x = 0; x < vinfo.xres; ++x) {
            plot(x, y, backgroundColor);
        }
    }
}

void FrameBuffer::plot(int x, int y, Color& c) {
    int location = ((x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length) % this->screenSize;

    *(fbp + location) = c.b;
    *(fbp + location + 1) = c.g;
    *(fbp + location + 2) = c.r;
    *(fbp + location + 3) = 0;
}

Color * FrameBuffer::getColor(int x, int y) {
    int location = ((x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length) % this->screenSize;
    Color * c = new Color();
    c->b = *(fbp + location);
    c->g = *(fbp + location + 1);
    c->r = *(fbp + location + 2);

    return c;
}