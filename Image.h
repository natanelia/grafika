#ifndef _IMAGE
#define _IMAGE
#include "ShadowBuffer.h"
#include "Drawing.h"
#include <cstring>

using namespace std;

class Image : public Drawing {
public:
    Color color;
    Image(vector<Point>& points);
    Image(Point points[], int n);

    void draw(ShadowBuffer &sb);
    void clear(ShadowBuffer &sb);
};

#endif