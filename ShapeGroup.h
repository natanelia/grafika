#ifndef __SHAPEGROUP
#define __SHAPEGROUP
#include "ShadowBuffer.h"
#include "Shape.h"
#include "util.cpp"

class ShapeGroup {
public:
    Color color;
    vector<Shape> shapes;

    ShapeGroup(string objName);

    void draw(ShadowBuffer& sb);
    void drawView(ShadowBuffer& sb);
    void translate(float dX, float dY);
    void scale(Point axis, float scalingFactorX, float scalingFactorY);
    void rotate(Point axis, float angle);
    void clip(Point min, Point max, float scale);

    Point * getTipPoints();
};

#endif