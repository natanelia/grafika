#ifndef __SHAPEGROUP
#define __SHAPEGROUP
#include "ShadowBuffer.h"
#include "Shape.h"
#include "util.cpp"

class ShapeGroup {
public:
    Color color;
    vector<Shape> shapes;
    vector<vector<Point> > pointToPrint;


    ShapeGroup(string objName);

    void setPointToDraw();
    void draw(ShadowBuffer& sb);
    void drawView(ShadowBuffer& sb);
    void translate(float dX, float dY);
    void scale(Point axis, float scalingFactorX, float scalingFactorY);
    void rotate(Point axis, float angle);
    void clip(Point min, Point max, float scale);
    vector<vector<Line> > initAvailable(int x1, int x2);
    bool findIntersection(Point p1, Point p2, int y, int &x, int &z);
    int findZMax(vector<Point> plane);
    void sortLayer();
    vector<Point> sortVector(vector<Point> v);
    void splitAvailable(vector<vector<Line> > &Available, vector<Point> demand, ShadowBuffer& sb, Color c);
    void scanLineFill3D(ShadowBuffer& sb);
    Point * getTipPoints();
};

#endif