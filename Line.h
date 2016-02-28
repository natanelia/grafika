#ifndef _LINE
#define _LINE
#include "ShadowBuffer.h"
#include "Drawing.h"

class Line : public Drawing {
public:
    Color color;

    Line(vector<Point>& points);
    Line(Point points[], int n);
    Line(Point p1, Point p2);
    
    Point getPoint1();
    Point getPoint2();
    void draw(ShadowBuffer& sb);
};

#endif