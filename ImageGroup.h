#ifndef __IMAGEGROUP
#define __IMAGEGROUP
#include "ShadowBuffer.h"
#include "Image.h"
#include "util.cpp"
#include "ColorTable.h"
#include <string>
#include <sstream>
#include <map>
#include <vector>

class ImageGroup {    
public:
    vector<Image> images;

    ImageGroup(string filename, string posname, float offsetX, float offsetY, int scale);
    void insertPosition(string filename, int offsetX, int offsetY, int scale);

    void draw(ShadowBuffer& sb);
    void translate(float dX, float dY,float dZ);
    // void rotateX(float degree, float offsetX, float offsetY, float offsetZ);
    // void rotateY(float degree, float offsetX, float offsetY, float offsetZ);
    // void rotateZ(float degree, float offsetX, float offsetY, float offsetZ);
    void rotatePositionX(float degree, float offsetX, float offsetY, float offsetZ);
    void rotatePositionY(float degree, float offsetX, float offsetY, float offsetZ);
    void rotatePositionZ(float degree, float offsetX, float offsetY, float offsetZ);
};

#endif