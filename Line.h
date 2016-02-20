#ifndef _LINE
#define _LINE
#include "ShadowBuffer.h"
#include "Drawing.h"

class Line : public Drawing {
public:
    Color color;

    Line(vector<Point>& points);
    Line(Point points[], int n);

    void draw(ShadowBuffer& sb);
};

#endif