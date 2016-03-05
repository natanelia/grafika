#ifndef _LINE
#define _LINE
#include "ShadowBuffer.h"
#include "Drawing.h"

class Line : public Drawing {
protected:
    Point projectPointToLine(Point p);

public:
    Color color;

    Line(vector<Point>& points);
    Line(Point points[], int n);
    Line(Point p1, Point p2);
    
    Point getPoint1();
    Point getPoint2();
    void draw(ShadowBuffer& sb);
    void draw(ShadowBuffer& sb, Point const baseStart, int const radius, Color const startColor, Color const endColor);
    void drawChopped(ShadowBuffer& sb, Point const baseStart, int const radius, Color const startColor, Color const endColor, int n);

    void draw(ShadowBuffer& sb, Point const baseStart, float * radius, Color * colors, int n);
    void drawChopped(ShadowBuffer& sb, Point const baseStart, float * radius, Color * colors, int n, int nSegment);
};

#endif