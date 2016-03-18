#include "ShadowBuffer.h"

using namespace std;

ShadowBuffer::ShadowBuffer(int width, int height, int offsetX, int offsetY, int lineLength) {
    this->width = width;
    this->height = height;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->lineLength = lineLength;
    this->bufferSize = this->width * this->height * 4;

    this->sfbp = new char[this->bufferSize];
}

void ShadowBuffer::draw() {
    this->clear();

    for (int i = 0; i < shadows.size(); ++i) {
        for (int y = 0; y < shadows[i]->height; y++) {
            for (int x = 0; x < shadows[i]->width; x++) {
                memcpy(sfbp + ((x + shadows[i]->offsetX) * 4 + (y + shadows[i]->offsetY) * shadows[i]->lineLength), shadows[i]->sfbp + ((x * 4 + y * shadows[i]->lineLength) % shadows[i]->bufferSize), 4);
            }
        }
    }
}

void ShadowBuffer::clear() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            plot(x, y, backgroundColor);
        }
    }
}

void ShadowBuffer::plot(int x, int y, Color& c) {
    int location = abs(x * 4 + y * this->lineLength);
    if(location <= bufferSize) {
        *(sfbp + location) = c.b;
        *(sfbp + location + 1) = c.g;
        *(sfbp + location + 2) = c.r;
        *(sfbp + location + 3) = 0;
    }
}

Color * ShadowBuffer::getColor(int x, int y) {
    int location = abs(x * 4 + y * this->lineLength) % this->bufferSize;
    Color * c = new Color();
    c->b = *(sfbp + location);
    c->g = *(sfbp + location + 1);
    c->r = *(sfbp + location + 2);

    return c;
}